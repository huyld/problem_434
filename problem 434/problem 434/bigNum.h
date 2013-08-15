#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class bigNum {
	vector<char> num;
	//bool sign;			//if true; this bigNum is negative
public:
	bigNum();

	unsigned int length();
	bool isNum();
	void reset();
	
	int operator[](const int &x);
	bigNum operator=(const bigNum &b);
	bigNum operator=(const int &b);

	//comparision
	bool operator>(const bigNum &b);
	bool operator==(const bigNum &b);
	bool operator<(const bigNum &b);
	bool operator>=(const bigNum &b);

	//arithmetics
	bigNum operator+(const bigNum &b);
	bigNum operator+(const char &b);
	bigNum operator-(const bigNum &b);	//condition: *this >= b

	bigNum operator*(const long &b);
	bigNum operator*(const bigNum &b);
	bigNum operator/(const long &b);
	long operator%(const long &b);
	bigNum operator/(const bigNum &b);
	bigNum operator%(const bigNum &b);


	//I/O
	void input();
	void output();
};