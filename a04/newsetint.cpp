/*
 * setint.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: georgeli
 */

#include "newsetint.h"
using namespace std;

bool SetInt::isSorted() const
{
	return true;
}

SetInt::SetInt()
{
	intList = new node();
	intList->next = NULL;
	intList->value = 0;
}

SetInt::SetInt(int i)
{
	intList = new node();
	node *temp = new node();
	intList->next = temp;
	intList->value = 0;
	temp->value = i;
}

SetInt::SetInt(const SetInt& setint)
{
	intList = new node(*setint.intList);
}

SetInt::~SetInt()
{
	delete intList;
}

void SetInt::nullify()
{
	intList->~node();
}

bool SetInt::isNull() const
{
	return intList->next == NULL;
}

int SetInt::SIZE() const
{
	return intList->length();
}

void SetInt::output() const
{
	//compute a sorted vector with same elements of IntVector
	node *temp = intList->next;
	//print sorted vector
	while(temp != NULL)
	{
	    cout << temp->value << endl;
	    temp = temp->next;
	}
}

bool SetInt::isMember(int i) const
{
	return intList->hasValue(i);
}

SetInt SetInt::operator +(const SetInt& rtSide)  // Union
{
	SetInt newst;

	node *templs = intList->next;
	node *temprs = rtSide.intList->next;
	node *cur = newst.intList;

	bool left;
	while(templs || temprs)
	{
		if(!templs)
			left = false;
		else if(!temprs)
			left = true;
		else if(templs->value > temprs->value)
			left = false;
	    else if(templs->value < temprs->value)
	    	left = true;
	    else
	    {
	    	left = true;
	    	temprs = temprs->next;
	    }

		if(left)
		{
			cur->next = new node(templs->value);
		 	cur = cur->next;
			templs = templs->next;
		}
		else
		{
			cur->next = new node(temprs->value);
		 	cur = cur->next;
			temprs = temprs->next;
		}
	}

	return newst;
}

SetInt SetInt::operator *(const SetInt& rtSide)  // Intersection
{
	SetInt newst;

	node *templs = intList->next;
	node *temprs = rtSide.intList->next;
	node *cur = newst.intList;

	while(templs && temprs)
	{
		if(templs->value == temprs->value)
		{
			cur->next = new node(templs->value);
			cur = cur->next;
			templs = templs->next;
			temprs = temprs->next;
		}
	    else if(templs->value < temprs->value)
	    	templs = templs->next;
	    else
	    	temprs = temprs->next;
	}

	return newst;
}
SetInt SetInt::operator -(const SetInt& rtSide)  // Set subtraction
{
	SetInt newst;

	node *templs = intList->next;
	node *temprs = rtSide.intList->next;
	node *cur = newst.intList;

	bool addnew;
	while(templs)
	{

		if(!temprs)
			addnew = true;
		else if(templs->value > temprs->value)
			addnew = false;
	    else if(templs->value < temprs->value)
	    	addnew = true;
	    else
	    {
	    	templs = templs->next;
	    	temprs = temprs->next;
	    	continue;
	    }

		if(addnew)
		{
			cur->next = new node(templs->value);
		 	cur = cur->next;
			templs = templs->next;
		}
		else if (temprs)
			temprs = temprs->next;
	}

	return newst;
}

SetInt& SetInt::operator =  (const SetInt& rtSide)  // Assignment
{
	delete intList;

	const node* from = rtSide.intList;

	intList = new node();
	node *cur = intList;

	do
	{
		cur->value = from->value;

		if(from->next)
			cur->next = new node();
		else
			cur->next = NULL;

		from = from->next;

		cur = cur->next;

	}while(from != NULL);

	return *this;
}
