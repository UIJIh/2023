#include "inf_int.h"

inf_int::inf_int()
{
	this->digits = new char[2];

	this->digits[0] = '0';		// default = '0'
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// when (-)
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// convert to string
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {
		new (this) inf_int();
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(const char* str)
{
	std::string s(str);
	if (s[0] == '-') {
		thesign = false;
		s.erase(s.begin() + 0);
	}
	else {
		thesign = true;
	}
	// reverse
	std::reverse(s.begin(), s.end());
	length = s.length();
	const char* temp_str = s.c_str();
	digits = new char[length + 1];
	strcpy(digits, temp_str);
}

inf_int::inf_int(const inf_int& a) {
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() {
	delete digits;		// deallocation
}

inf_int& inf_int::operator=(const inf_int& a)
{
	if (this->digits) {
		delete this->digits;		// delete when it exists already
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// same sign, same digits
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	// different sign
	if (a.thesign && !b.thesign) {
		return true;
	}
	else if (!a.thesign && b.thesign) {
		return false;
	}
	else {
		// same sign

		// different length
		if (a.length < b.length) {
			return !a.thesign;
		}
		else if (a.length > b.length) {
			return a.thesign;
		}
		else {
			// same length
			for (int i = a.length - 1; i >= 0; i--) {
				if (a.digits[i] < b.digits[i]) {
					return !a.thesign;
				}
				else if (a.digits[i] > b.digits[i]) {
					return a.thesign;
				}
			}
			// same every conditions
			return false;
		}
	}
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// same sign
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else {	// different sign
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	inf_int left(a);
	inf_int right(b);

	if (left == right) {
		return inf_int(0);
	}

	std::string strNormal;
	std::string strComplement;
	bool signFlag = false;

	// case1 : (+a - +b)
	// + - +
	if (a.thesign == 1 && b.thesign == 1) { 
		// if a < b -> swap
		if (operator<(left, right)) {
			right = a;
			left = b;
			signFlag = true; // later changed
		}
		// covert to string
		std::string strNormal = left.digits;
		std::string strComplement = right.digits; 

		// adjust digits adding 0
		int absLen = abs((int)(strNormal.length() - strComplement.length()));
		for (int i = 0; i < absLen; i++) {
			strComplement += '0';
		}

		// the 10's complement
		for (int i = 0; i < strComplement.length(); i++) {
			strComplement[i] = '9' - strComplement[i] + '0';
		}
		strComplement[0]++; // the most left digit

		reverse(strComplement.begin(), strComplement.end());
		reverse(strNormal.begin(), strNormal.end());

		inf_int a(strComplement.c_str());
		inf_int b(strNormal.c_str());
		inf_int result = a + b;

		// adjust digits
		std::string cut(result.digits); 
		reverse(cut.begin(), cut.end());
		cut.erase(cut.begin());

		for (int i = 0;;) {
			if (cut[i] == '0') {
				cut.erase(cut.begin());
			}
			else if (cut[i] != '0') {
				break;
			}
		}

		inf_int resultValue(cut.c_str());
		// changed the sign again
		if (signFlag) {
			resultValue.thesign = false;
		}
		return resultValue;
	}

	// case2 : (-a - -b) = -(+a -b) 
	// - - -
	if (a.thesign == 0 && b.thesign == 0) {
		right = a;	left = b;
		left.thesign = 1;
		right.thesign = 1;
		inf_int resultValue = left - right;
		return resultValue;
	}

	// case3 : (+a - -b)
	// + - -
	if (a.thesign == 1 && b.thesign == 0) {
		right.thesign = 1;
		inf_int resultValue = left + right;
		resultValue.thesign = 1;
		return resultValue;
	}

	// case4 : (-a - +b) = -(+a + +b)
	// - - +
	if (a.thesign == 0 && b.thesign == 1) {
		left.thesign = 1;
		inf_int resultValue = left + right;
		resultValue.thesign = 0;
		return resultValue;
	}
}

inf_int operator*(const inf_int& a, const inf_int& b)
{	// a * b
	inf_int multiplicand = a; 
	inf_int multiplier = b;
	inf_int result(0);
	multiplicand.thesign = true;
	multiplier.thesign = true;

	for (int i = 0; i < strlen(a.digits); i++) {
		int currentDigit = a.digits[i] - '0';

		for (int i = 0; i < currentDigit; i++) {
			result = result + multiplier;  
		}

		// when multiplying 123 and 456, start with the rightmost digit of 123 (3) and multiply it by 456
		// then move to the next digit(2), multiply it by 456 
		std::string multiplier10(multiplier.digits); 
		if (strcmp(multiplier10.c_str(), "0")) {
			multiplier10 = "0" + multiplier10; // to the next == multiple 10
		}
		std::reverse(multiplier10.begin(), multiplier10.end());
		multiplier = *(new inf_int(multiplier10.c_str()));
	}

	if (a.thesign ^ b.thesign) {
		result.thesign = false;
	}

	if (!strcmp(result.digits, "0")) {
		result.thesign = true;
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const inf_int& a)
{
	int i;

	if (!a.thesign) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// adding n to the following index 
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// exception
			std::cout << "Memory reallocation failed, the program will terminate." << std::endl;
			exit(0);
		}

		this->length = index;					
		this->digits[this->length] = '\0';	
	}

	if (this->digits[index - 1] < '0') {
		this->digits[index - 1] = '0';
	}
	// operation
	this->digits[index - 1] += num - '0';	

	if (this->digits[index - 1] > '9') {	// a carry 
		this->digits[index - 1] -= 10;	// subtract 10 (in ASCII) from the current digit
		Add('1', index + 1);			// add 1 to the digit in the next position (carry)
	}
}
