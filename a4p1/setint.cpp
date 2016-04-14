/*
 * setint.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: georgeli
 */

#include "setint.h"
using namespace std;

bool SetInt::isSorted() const
{
	for( unsigned i = 0; i < intVector.size() - 1; i++)
		if(intVector.at(i) > intVector.at(i+1))
			return false;

	return true;
}

SetInt::SetInt()
{

}

SetInt::SetInt(int i)
{
	intVector.push_back(i);
}

void SetInt::nullify()
{
	intVector.clear();
}

bool SetInt::isNull() const
{
	return intVector.empty();
}

int SetInt::SIZE() const
{
	return intVector.size();
}

void SetInt::output() const
{
	//compute a sorted vector with same elements of IntVector
	vector<int> newIntVector;

	if(intVector.size() > 0)
		newIntVector.push_back(intVector.at(0));

	for(unsigned i = 1; i < intVector.size(); i++)
	{
		std::vector<int>::iterator it;
		it = newIntVector.begin();
		int num = intVector.at(i);

		bool inserted = false;
		while(it != newIntVector.end())
		{
			if(num < *it)
			{
				newIntVector.insert(it, num);
				inserted = true;
				break;
			}
			it++;
		}
		if(!inserted)
			newIntVector.push_back(num);
	}

	//print sorted vector
	for( unsigned i = 0; i < newIntVector.size(); i++)
	{
	    cout << newIntVector.at(i) << endl;
	}
}

bool SetInt::isMember(int i) const
{
	for( unsigned j = 0; j < intVector.size(); j++)
	{
	    if(intVector.at(i)==i) // not it
	    return true;
	}
	return false;
}

SetInt SetInt::operator +(const SetInt& rtSide)  // Union
{
	SetInt newst;

	for( unsigned i = 0; i < intVector.size(); i++)
	{
		bool hadDuplicate = false;
		int ivi = intVector.at(i);
		for( unsigned j = 0; j < rtSide.intVector.size(); j++)
		    if(ivi == rtSide.intVector.at(j))
		    {
		    	hadDuplicate=true;
		    	break;
		    }

		if(!hadDuplicate)
			newst.intVector.push_back(ivi);
	}

	for( unsigned j = 0; j < rtSide.intVector.size(); j++)
	{
		int tt = rtSide.intVector.at(j);
		newst.intVector.push_back(tt);
	}

	return newst;
}
SetInt SetInt::operator *(const SetInt& rtSide)  // Intersection
{
	SetInt newst;

	for( unsigned i = 0; i < intVector.size(); i++)
	{
		int ivi = intVector.at(i);

		for( unsigned j = 0; j < rtSide.intVector.size(); j++)
		    if(ivi == rtSide.intVector.at(j))
		    {
		    	newst.intVector.push_back(ivi);
		    	break;
		    }
	}

	return newst;
}
SetInt SetInt::operator -(const SetInt& rtSide)  // Set subtraction
{
	SetInt newst;

	for( unsigned i = 0; i < intVector.size(); i++)
	{
		bool hadDuplicate = false;
		int ivi = intVector.at(i);

		for( unsigned j = 0; j < rtSide.intVector.size(); j++)
		    if(ivi == rtSide.intVector.at(j))
		    {
		    	hadDuplicate=true;
		    	break;
		    }

		if(!hadDuplicate)
			newst.intVector.push_back(ivi);
	}

	return newst;
}
// SetInt& operator =  (const SetInt& rtSide);  // Assignment
