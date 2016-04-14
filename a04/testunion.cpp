/*
 * testunion.cpp
 *
 *  Created on: Mar 22, 2013
 *      Author: georgeli
 */

// File testunion.cpp -- Exercise union routine in newsetint.cpp

#include "newsetint.h"
#include <iostream>
using namespace std;
int main () {

	SetInt st1, st2, st3; // An example Ð declaring sets

	cout<< "set1:"<<endl;
	st1.output();
	cout << endl;
	cout<< "set2:"<<endl;
	st2.output();
	cout << endl;
	cout<< "set3:"<<endl;
	st3.output();
	cout << endl;

	// test 1: simple union for empty sets
	cout << "union: set1 = set2 + set3" << endl << endl << "set1" << endl;
	st1 = st2 + st3;
	st1.output();
	cout << endl;

	// test 2: simple union for multiple single sets in different union orders
	// to see the result of adding set of multiple elements in different orders and set sizes
	cout << "union tests for set2: simple union for multiple single sets in different union orders" << endl;
	st2=SetInt(234) + SetInt(-324) + SetInt(12312) + SetInt(3) + SetInt(0) + SetInt(-90);
	st2.output();
	cout << endl;

	st2=SetInt(234) + (SetInt(-324) + SetInt(12312) + SetInt(3)) + (SetInt(0) + SetInt(-90));
	st2.output();
	cout << endl;

	st2=SetInt(234) + (SetInt(-324) + SetInt(12312)) + SetInt(3) + (SetInt(0) + SetInt(-90));
	st2.output();
	cout << endl;

	// test3: extended from test 2, adding union with multiple of the same numbers
	cout << "union tests for set2: simple union for multiple single sets in different orders" << endl;
	cout << "adding union with same numbers appearing in the union" << endl;
	st2=SetInt(234) + SetInt(-324) + SetInt(12312) + SetInt(3) + SetInt(0) + SetInt(12312) + SetInt(3) + SetInt(-90) + SetInt(-324);
	st2.output();
	cout << endl;

	st2=SetInt(234) + (SetInt(-324) + SetInt(12312) + SetInt(3) + SetInt(0)) + (SetInt(12312) + SetInt(3) + SetInt(-90)) + SetInt(-324);
	st2.output();
	cout << endl;

	st2=SetInt(234) + SetInt(-324) + SetInt(12312) + SetInt(3) + SetInt(0) + SetInt(12312) + (SetInt(3) + SetInt(-90) + SetInt(-324));
	st2.output();
	cout << endl;

	// test 4: adding empty set to non empty set, testing left and right side of +
	// this also tests if the return value of + is a proper SetInt
	cout << "adding empty set to non empty set, testing left and right side of +" << endl;
	(st2 + st3).output();
	cout << endl;
	(st3 + st2).output();
	cout << endl;

	// test 5: continue a test 4, two non empty set union, and output
	(SetInt(879) + st2).output();
	cout << endl;


}



