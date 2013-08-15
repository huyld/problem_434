#include "bigNum.h"



bigNum::bigNum() {
	num.insert(num.begin(), '0');
}




unsigned int bigNum::length() {
	unsigned int l = this->num.size();
	return l;
}

bool bigNum::isNum() {
	for(unsigned int i=0; i<num.size(); ++i) {
		if(int(num[i])<48 || int(num[i])>57)
			return false;
	}
	return true;
}

void bigNum::reset() {
	num.clear();
}




int bigNum::operator[](const int &x) {
	return int(num[x]) - 48;
}


bigNum bigNum::operator=(const bigNum &b) {
	if(&b==this)		//sefl-copy check
		return *this;
	
	this->reset();
	if(b.num.size()!=0) {
		char tmp;
		for(unsigned int i=0; i<b.num.size(); ++i) {
			tmp = b.num[i];
			this->num.push_back(tmp);
		}
	}
	return *this;
}

bigNum bigNum::operator=(const int &in) {
	reset();
	int b = in;

	if(b==0) {
		num.insert(num.begin(), '0');
		return *this;
	}

	int x;
	while(b!=0) {
		x = b % 10;
		num.insert(num.begin(), char(x + 48));
		b /= 10;
	}
	return *this;
}




bool bigNum::operator>(const bigNum &in) {
	bigNum a = *this;
	bigNum b = in;
	while(a.length() < b.length()) {
		a.num.insert(a.num.begin(), '0');
	}
	while(a.length() > b.length()) {
		b.num.insert(b.num.begin(), '0');
	}

	for(int i=0; i<a.length(); ++i) {
		if(a[i]<b[i])
			return false;
		if(a[i]>b[i])
			return true;
	}

	return false;
}



bool bigNum::operator==(const bigNum &in) {
	bigNum a = *this;
	bigNum b = in;
	while(a.length() < b.length()) {
		a.num.insert(a.num.begin(), '0');
	}
	while(a.length() > b.length()) {
		b.num.insert(b.num.begin(), '0');
	}

	for(unsigned int i=0; i<a.length(); ++i) {
		if(a[i]!=b[i])
			return false;
	}
	return true;
}


bool bigNum::operator<(const bigNum &in) {
	bigNum a = *this;
	bigNum b = in;
	while(a.length() < b.length()) {
		a.num.insert(a.num.begin(), '0');
	}
	while(a.length() > b.length()) {
		b.num.insert(b.num.begin(), '0');
	}

	for(int i=0; i<a.length(); ++i) {
		if(a[i]>b[i])
			return false;
		if(a[i]<b[i])
			return true;
	}

	return false;
}

bool bigNum::operator>=(const bigNum &in) {
	if(*this<in)
		return false;
	return true;
}




bigNum bigNum::operator+(const bigNum &in) {
	//initialte
	bigNum result;
	bigNum a = *this;
	bigNum b = in;
	
	while(a.length() < b.length())
		a.num.insert(a.num.begin(), '0');
	while(a.length() > b.length())
		b.num.insert(b.num.begin(), '0');

	result.reset();
	int x, y, sum;
	int carry = 0;
	for(int i=a.length()-1; i>=0; --i) {
		x = a[i];
		y = b[i];
		sum = x + y + carry;
		carry = sum/10;
		sum %= 10;
		result.num.insert(result.num.begin(), char(sum+48));
	}
	if(carry>0) {
		result.num.insert(result.num.begin(), '1');
	}
		
	return result;
}

bigNum bigNum::operator+(const char &in) {
	bigNum result;
	char b = in;
	if((int(b)-48) == 0)	//if b == 0
		return *this;

	int carry = 0;
	int x = 0;
	result.reset();
	for(int i=num.size()-1; i>=0; --i) {
		x = num[i];
		x = x + carry + (int(b) - 48);
		result.num.push_back(char(x));
		if(x>9) {
			carry = 1;
		}
		carry = 0;
	}
	if(carry != 0)
		result.num.insert(result.num.begin(), carry);
	return result;
}




bigNum bigNum::operator-(const bigNum &in) {
	//initialte
	bigNum result;
	result.reset();
	bigNum a = *this;
	bigNum b = in;
	
	while(a.length() < b.length())
		a.num.insert(a.num.begin(), '0');
	while(a.length() > b.length())
		b.num.insert(b.num.begin(), '0');

	int borrow = 0;
	int x, y, sub;

	for(int i=a.length()-1; i>=0; --i) {
		x = a[i];
		y = b[i];
		sub = x - y - borrow;
		if(sub<0) {
			sub += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		result.num.insert(result.num.begin(), char(sub+48));
	}

	while(result.num.size()>0 && result[0]==0)
		result.num.erase(result.num.begin());
	
	return result;
}




bigNum bigNum::operator*(const long &b) {
	//initialte
	bigNum result;
	long carry = 0;
	int mul, x;

	if(b==0)		//if b is 0, then return 0
		return result;

	result.reset();
	for(int i=num.size()-1; i>=0; --i) {
		x = (int(num[i]) - 48);
		mul = x*b + carry;
		carry = mul/10;
		mul %= 10;
		result.num.insert(result.num.begin(), char(mul+48));
	}

	int tmp = 0;
	while(carry != 0) {
		tmp = carry % 10;
		result.num.insert(result.num.begin(), char(tmp+48));
		carry /= 10;
	}

	return result;		
}


bigNum bigNum::operator*(const bigNum &in) {
	//initialte
	bigNum result;
	bigNum b = in;
	bigNum mul;
	int m = -1;

	if(b.num.size()==1 && b[0]==0)
		return result;

	result.reset();
	for(int i=num.size()-1; i>=0; --i) {
		++m;
		mul = b * (int(num[i]) - 48);
		for(int j=1; j<=m; ++j) {
			mul.num.push_back('0');
		}
		result = result + mul;
	}
	return result;
}




bigNum bigNum::operator/(const long &b) {
	//initialte
	bigNum result;
	long q = 0;
	long hold = 0;

	if(b==0) {
		return result;
	}
	
	result.reset();
	for(long i=0; i<num.size(); ++i) {
		hold = hold*10 + (int(num[i]) - 48);
		q = hold/b;
		hold %= b;
		result.num.push_back(char(q + 48));
	}

	while(result.num.size()>0 && result[0]==0)
		result.num.erase(result.num.begin());
	return result;
}

long bigNum::operator%(const long &b) {
	long hold = 0;
	
	for(int i=0; i<num.size(); ++i) {
		hold = (int(num[i]) - 48 + hold*10) % b;
	}

	return hold;
}




bigNum bigNum::operator/(const bigNum &b) {
	bigNum result, hold;
	bigNum kb[11];
	long k = 1;

	kb[0] = 0;
	for(int i=1; i<11; ++i)
		kb[i] = kb[i-1] + b;
	hold.reset();
	result.reset();

	for(int i=0; i<num.size(); ++i) {
		hold.num.push_back(num[i]);
		k = 1;
		while(hold>=kb[k])
			++k;
		result.num.push_back(char(k - 1 + 48));
		hold = hold - kb[k-1];
	}
	while(result.num.size()>0 && result[0]==0)
		result.num.erase(result.num.begin());
	
	return result;
}

bigNum bigNum::operator%(const bigNum &b) {
	bigNum hold;
	bigNum kb[11];
	long k = 1;

	kb[0] = 0;
	for(int i=1; i<11; ++i)
		kb[i] = kb[i-1] + b;
	hold.reset();

	for(int i=0; i<num.size(); ++i) {
		hold.num.push_back(num[i]);
		k = 1;
		while(hold>=kb[k])
			++k;
		hold = hold - kb[k-1];
	}
	return hold;
}














void bigNum::input() {
	std::cout << "Please enter a number: ";
	bigNum tmp;
	string buf;
	char c;

	tmp.reset();
	std::getline(std::cin, buf);
	for(unsigned int i=0; i<buf.length(); ++i) {
		c = buf[i];
		if(int(c)<48 || int(c)>57) {	//if the buf string does not represent a number
			tmp.reset();
			return;
		}
		tmp.num.push_back(c);
	}
	num = tmp.num;
	return;
}

void bigNum::output() {
	for(unsigned int i=0; i<num.size(); ++i)
		std::cout << num[i];
	return;
}