#pragma once
#include "inf_int.h"
#include "string"
#include "vector"

using namespace std;

class Calculator {
public:
	Calculator();

	void getInput();
	bool isInteger(const string& str); // if input has non-integer
	vector<string> split(string str, char delimiter);  // to split by space

	inf_int add(inf_int a, inf_int b);
	inf_int subtract(inf_int a, inf_int b);
	inf_int multiply(inf_int a, inf_int b);
};