#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include "help.h"
#include "setint.h"
using namespace std;

vector<string> setId;
vector<SetInt> setValue;

bool checkCmd(string &x) {
	if (x[0] != 'e' && x[0] != '=' && x[0] != 'i' && x[0] != 'p' && x[0] != '+'
			&& x[0] != '-' && x[0] != '*' && x[0] != 'q' && x[0] != '?') {
		cerr << "ERROR, Ignoring character " << x[0] << endl;
		return false;
	}
	return true;
}

SetInt& getSetInt(string id) {
	SetInt temp;
	for (unsigned i = 0; i < setId.size(); i++) {
		if (setId.at(i) == id)
			return setValue.at(i);
	}

	setId.push_back(id);
	setValue.push_back(temp);

	return setValue.back();
}

string intoken() {
	if (cin.eof())
		exit(0);

	string input;
	cin >> input;

	return input;
}

int main() {
	cout << "Driver for set operations. Type '?' for help." << endl;

	string input = "";
	char cmd = 0;

	while (!cin.eof()) {
		switch (cmd) {
		case 0:
			cout << "Command: ";

			if (input.length() == 0)
				input = intoken();

			if (checkCmd(input))
				cmd = input[0];

			if (input.length() != 0)
				input = input.substr(1, input.length() - 1);
			break;

		case 'e':
			if (input.length() == 0)
				input = intoken();
			cout << input << endl;
			input = "";
			cmd = 0;
			break;

		case '?':
			help();
			input = "";
			cmd = 0;
			break;
		case 'q':
			return 0;
		case 'i': {
			cout << "Init: x = { int1 int2 ... intN }: ";
			if (input.length() == 0)
				input = intoken();
			//get set id
			string sid = input;
			SetInt temp;
			//get = {
			input = intoken();
			if (input != "=")
				cerr << "ERROR, Missing '=' got " << input << endl;
			input = intoken();
			if (input != "{")
				cerr << "ERROR, Missing '{' got " << input << endl;

			//get numbers and }

			input = intoken();
			while (input != "}") {
				char c = input[0];
				int n = 0;
				bool isNeg = false;
				if (c == '-')
				{
					isNeg = true;
					input = input.substr(1, input.length() - 1);
				}

				for (unsigned i = 0; i < input.length(); i++) {
					c = input[i];
					if (!(c >= 48 && c <= 57))
						break;

					n *= 10;
					n += c - 48;
				}

				if(isNeg)
					n*=-1;

				SetInt temp1(n);
				temp = temp + temp1;
				input = intoken();
			}

			getSetInt(sid) = temp;

			input = "";
			cmd = 0;

			break;
		}
		case 'p': {
			cout << "Print. Give set name: ";
			if (input.length() == 0)
				input = intoken();

			SetInt temp = getSetInt(input);

			temp.output();
			if (temp.isNull())
				cout << "Empty set" << endl;

			cmd = 0;
			input = "";
			break;
		}
		case '+': {
			cout << "Union. var1 = var2 + var3: ";
			if (input.length() == 0)
				input = intoken();

			string id = input;

			input = intoken();
			if (input != "=")
				cerr << "ERROR, Missing '=' got " << input << endl;

			input = intoken();
			SetInt v2 = getSetInt(input);

			input = intoken();
			if (input != "+")
				cerr << "ERROR, Missing '+' got " << input << endl;

			input = intoken();
			SetInt v3 = getSetInt(input);

			getSetInt(id) = v2 + v3;
			input = "";
			cmd = 0;
			break;
		}
		case '-': {
			cout << "Subtraction. var1 = var2 - var3: ";
			if (input.length() == 0)
				input = intoken();

			string id = input;

			input = intoken();
			if (input != "=")
				cerr << "ERROR, Missing '=' got " << input << endl;

			input = intoken();
			SetInt v2 = getSetInt(input);

			input = intoken();
			if (input != "-")
				cerr << "ERROR, Missing '-' got " << input << endl;

			input = intoken();
			SetInt v3 = getSetInt(input);

			getSetInt(id) = v2 - v3;

			input = "";
			cmd = 0;
			break;
		}
		case '*': {
			cout << "Intersection. var1 = var2 * var3: ";
			if (input.length() == 0)
				input = intoken();

			string id = input;

			input = intoken();
			if (input != "=")
				cerr << "ERROR, Missing '=' got " << input << endl;

			input = intoken();
			SetInt v2 = getSetInt(input);

			input = intoken();
			if (input != "*")
				cerr << "ERROR, Missing '*' got " << input << endl;

			input = intoken();
			SetInt v3 = getSetInt(input);

			getSetInt(id) = v2 * v3;

			input = "";
			cmd = 0;
			break;
		}
		case '=': {
			cout << "Assign: x = y: ";

			if (input.length() == 0)
				input = intoken();
			//get set id
			string id1 = input;
			//get = {
			input = intoken();
			if (input != "=")
				cerr << "ERROR, Missing '=' got " << input << endl;
			input = intoken();
			string id2 = input;

			getSetInt(id1) = getSetInt(id2);

			input = "";
			cmd = 0;
			break;
		}
		default:
			break;
		}

	}
	return 0;
}
