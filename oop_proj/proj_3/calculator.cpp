#include "calculator.h"
#include "string"
#include "vector"
#include <sstream>
#include <iostream>

using namespace std;

Calculator::Calculator() {
	getInput();
}

bool Calculator::isInteger(const string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false; // if has non-number
		}
	}
	return true; 
}

void Calculator::getInput() {
	string input;
	while (1) {				// repeatedly
		cout << "Input: ";
		getline(cin, input);

		// terminate condition
		if (input == "0") break;

		vector<string> result = split(input, ' ');		// split by space

		// wrong input (shape/format)
		if (result.size() != 3) {
			cout << "Invalid Input! Try again : (positive integer)(space)(operator)(space)(positive integer)" << endl;
			cout << "\t\t\t\t1234567\t\t\t+\t\t   5678" << endl;
			continue; 
		}
		if (!isInteger(result[0])) {
			cout << "Invalid Input! Try again : (positive integer)(space)(operator)(space)(positive integer)" << endl;
			cout << "\t\t\t\t1234567\t\t\t+\t\t   5678" << endl;
			continue;
		}
		if (!isInteger(result[2])) {
			cout << "Invalid Input! Try again : (positive integer)(space)(operator)(space)(positive integer)" << endl;
			cout << "\t\t\t\t1234567\t\t\t+\t\t   5678" << endl;
			continue;
		}

		inf_int numFirst(result[0].c_str());
		inf_int numSecond(result[2].c_str());
		string operate = result[1]; // operator

		if (operate.compare("+") == 0) {
			cout << "Output: " << add(numFirst, numSecond) << endl;
		}
		else if (operate.compare("-") == 0) {
			cout << "Output: " << subtract(numFirst, numSecond) << endl;
		}
		else if (operate.compare("*") == 0) {
			cout << "Output: " << multiply(numFirst, numSecond) << endl;
		}
		else {
			cout << "Invalid Input! Try again : (positive integer)(space)(operator)(space)(positive integer)" << endl;
			cout << "\t\t\t\t1234567\t\t\t+\t\t   5678" << endl;
		}
	}
}
// to split
vector<string> Calculator::split(string str, char delimiter) { 
	istringstream stream(str); // input into stream (to read one-by-one)
	string token;             // buffer; store the separated        

	vector<string> result;

	while (getline(stream, token, delimiter)) { // getline(input, where to save, till meet-)
		result.push_back(token);               // store the separated to the vector
	}

	return result;
}

inf_int Calculator::add(inf_int a, inf_int b) {
	return a + b;
}

inf_int Calculator::subtract(inf_int a, inf_int b) {
	return a - b;
}

inf_int Calculator::multiply(inf_int a, inf_int b) {
	return a * b;
}