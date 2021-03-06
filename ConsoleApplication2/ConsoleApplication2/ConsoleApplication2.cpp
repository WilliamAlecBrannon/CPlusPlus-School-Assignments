// 1/n^3 / Apery's Constant helper by William Brannon
//Explanation: During my Calculus 2 class, we discussed the concept of p-series and how Euler found the value of the function for p = 2, and that there is a formula for all even p-values
//I was curious about the nature of Apery's constant and whether i could gain some insight towards finding a closed form represenation of it. This code is my attempt at gaining that insight
//TODO implement Fraction.reduceFraction with BigInt
//TODO visualize prime factorization https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BigInt {
public:
	vector<char> num;
	BigInt() {
		num.push_back('0');
	}
	BigInt(string input) {
		for (unsigned int n = 0; n < input.length(); n++) {
			num.push_back(input.at(n));
		}
	}
	string output() {
		string o;
		for (unsigned int n = 0; n < num.size(); n++) {
			o.push_back(num.at(n));
		}
		return o;
	}
	BigInt add(BigInt num1, BigInt num2)
	{
		string str1 = num1.output();
		string str2 = num2.output();
		// Before proceeding further, make sure length 
		// of str2 is larger. 
		if (str1.length() > str2.length())
			swap(str1, str2);

		// Take an empty string for storing result 
		string str = "";

		// Calculate length of both string 
		int n1 = str1.length(), n2 = str2.length();

		// Reverse both of strings 
		reverse(str1.begin(), str1.end());
		reverse(str2.begin(), str2.end());

		int carry = 0;
		for (int i = 0; i<n1; i++)
		{
			// Do school mathematics, compute sum of 
			// current digits and carry 
			int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
			str.push_back(sum % 10 + '0');

			// Calculate carry for next step 
			carry = sum / 10;
		}

		// Add remaining digits of larger number 
		for (int i = n1; i<n2; i++)
		{
			int sum = ((str2[i] - '0') + carry);
			str.push_back(sum % 10 + '0');
			carry = sum / 10;
		}

		// Add remaining carry 
		if (carry)
			str.push_back(carry + '0');

		// reverse resultant string 
		reverse(str.begin(), str.end());

		BigInt result = BigInt(str);
		return result;
	}
	BigInt multiply(BigInt a, BigInt b)
	{
		string num1 = a.output();
		string num2 = b.output();
		int len1 = num1.size();
		int len2 = num2.size();
		if (len1 == 0 || len2 == 0)
			return BigInt("0");

		// will keep the result number in vector 
		// in reverse order 
		vector<int> result(len1 + len2, 0);

		// Below two indexes are used to find positions 
		// in result.  
		int i_n1 = 0;
		int i_n2 = 0;

		// Go from right to left in num1 
		for (int i = len1 - 1; i >= 0; i--)
		{
			int carry = 0;
			int n1 = num1[i] - '0';

			// To shift position to left after every 
			// multiplication of a digit in num2 
			i_n2 = 0;

			// Go from right to left in num2              
			for (int j = len2 - 1; j >= 0; j--)
			{
				// Take current digit of second number 
				int n2 = num2[j] - '0';

				// Multiply with current digit of first number 
				// and add result to previously stored result 
				// at current position.  
				int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

				// Carry for next iteration 
				carry = sum / 10;

				// Store result 
				result[i_n1 + i_n2] = sum % 10;

				i_n2++;
			}

			// store carry in next cell 
			if (carry > 0)
				result[i_n1 + i_n2] += carry;

			// To shift position to left after every 
			// multiplication of a digit in num1. 
			i_n1++;
		}

		// ignore '0's from the right 
		int i = result.size() - 1;
		while (i >= 0 && result[i] == 0)
			i--;

		// If all were '0's - means either both or 
		// one of num1 or num2 were '0' 
		if (i == -1)
			return BigInt("0");

		// generate the result string 
		string s = "";

		while (i >= 0)
			s += std::to_string(result[i--]);

		BigInt output = BigInt(s);
		return output;
	}
};

class Fraction
{
	BigInt num, den;
public:
	Fraction() {
		num = BigInt("0");
		den = BigInt("1");
	};
	Fraction(BigInt a, BigInt b) {
		num = a;
		den = b;
	};
	Fraction(BigInt a) {
		num = a;
		den = BigInt("1");
	};
	Fraction(const Fraction& a) {
		num = a.num;
		den = a.den;
	};
	double toDouble() {
		return stod(num.output()) / stod(den.output());
	};
	BigInt numerator() const {
		return num;
	}
	BigInt denominator() const {
		return den;
	}
	string output() {
		return num.output() + "/" + den.output();
	};
	Fraction operator+(const Fraction &a)
	{   
		return Fraction(num.add(num.multiply(num,a.den),num.multiply(den,a.num)), den.multiply(den,a.den));
	}
	Fraction operator*(const Fraction &m)
	{
		return Fraction(num.multiply(num,m.num), den.multiply(den,m.den));
	}
	Fraction operator/(const Fraction &d)
	{
		return Fraction(num.multiply(num,d.den), den.multiply(den,d.num));
	}
	/*bool operator<(const Fraction &r) {
		double thisVal = this->toDecimal();
		double rVal = r.toDecimal();
		return thisVal < rVal;
	}
	bool operator<=(const Fraction &r) {
		double thisVal = this->toDecimal();
		double rVal = r.toDecimal();
		return thisVal <= rVal;
	}
	bool operator>(const Fraction &r) {
		double thisVal = this->toDecimal();
		double rVal = r.toDecimal();
		return thisVal > rVal;
	}
	bool operator>=(const Fraction &r) {
		double thisVal = this->toDecimal();
		double rVal = r.toDecimal();
		return thisVal >= rVal;
	}
	bool operator==(const Fraction &r) {
		double thisVal = this->toDecimal();
		double rVal = r.toDecimal();
		return thisVal == rVal;
	}
	bool operator!=(const Fraction &r) {
		double thisVal = this->toDecimal();
		double rVal = r.toDecimal();
		return thisVal != rVal;
	}
	void reduceFraction() {
		int gcd = 1;
		int largest = (num > den) ? num : den;
		for (int x = 2; x <= largest; ++x) {
			if (num % x == 0 && den % x == 0) {
				gcd = x;
			}
		}
		num = num / gcd;
		den = den / gcd;
	}*/
	Fraction operator=(const Fraction& a) {
		this->num = a.num;
		this->den = a.den;
		return *this;
	}
};

int main()
{
	Fraction Temp;
	Fraction Sum = Fraction(BigInt("0"),BigInt("1"));
	for (int n = 1; n < 21; n++) {
		int ncube = n * n * n;
		Temp = Fraction(BigInt("1"), BigInt(to_string(ncube)));
		//Temp.reduceFraction();
		Sum = Temp + Sum;
		//Sum.reduceFraction();
		cout << n << "," << Temp.output() << "," << Sum.output() << endl;
	}
	/*BigInt temp = BigInt("1243"); kept for reference
	BigInt temp2 = BigInt("45981");
	cout << temp.output() << "," << temp2.output() << "," << temp.add(temp, temp2).output() << "," << temp.multiply(temp,temp2).output() << endl;*/
	system("pause");
    return 0;
}