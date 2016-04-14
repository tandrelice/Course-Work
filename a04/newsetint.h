// Class setint.  Implements sets of integers
//     Overloads + for union, * for intersection, - for set
//     subtraction

#ifndef NEWSETINT
#define NEWSETINT

#include <iostream>
#include <vector>
using namespace std;

class node {
public :
	int value;
	struct node *next;

	// create a new empty node which represents an empty list of integer;
	// this is same as the "anchor" node specified by the assignment
	node()
	{
		value = 0;
		next = NULL;
	}
	// create a node with a number n as its value
	node(int n)
	{
		value = n;
		next = NULL;
	}
	// create a node with a number n as its value, next as its next node
	node(int n, node *next)
	{
		value = n;
		this->next = next;
	}
	// copy constructor and copy function, does same job
	node(const node &setint)
	{
		value = 0;
		next = NULL;
		node *cur = this;
		const node *from = &setint;

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
	}

	// destructor
	~node()
	{
		if(next != NULL)
		{
			next->~node();
			delete next;
			next = NULL;
		}
	}
	// insert a integer n to the list represent by this node, in order of low to high.
	void insert(int n)
	{
		node *temp = this;

		while(temp!=NULL)
		{
			if(temp->next == NULL)
				temp->next = new node(n);
			else if(temp->next->value == n)
				break;
			else if(temp->next->value > n)
			{
				temp->next = new node(n, temp->next);
				break;
			}
			temp = temp->next;
		}
	}

	// return the number of values in the list represented by this node
	int length()
	{
		int n = 0;
		node *temp = next;
		while(temp != NULL)
		{
			n++;
			temp = temp->next;
		}
		return n;
	}

	// tells if the linked list represented by this node has the value "int n" in it
	// yes->true, no->false
	bool hasValue(int n)
	{
		node *temp = next;
		while(temp != NULL)
		{
			if (temp->value == n)
				return true;
		}

		return false;
	}
};

class SetInt {
private:
	node *intList;
	// This is initially empty (when constructed)
	bool isSorted() const;

public:
	SetInt();  // Create empty set
	SetInt(const SetInt& setint);  // Copy Constructor
	~SetInt(); // Destructor

	// Correction to correction:  A comment here erroneously said
	//   that SetInt (int i) means "Insert i into set", which is wrong.
	//   The correct comment is given on the following line:
	SetInt(int i); // Create singleton set with i as member  

	void nullify(); // Make a set be empty
	bool isNull() const;
	int SIZE() const;

	void output() const;

	bool isMember(int i) const;

	SetInt operator +(const SetInt& rtSide);  // Union
	SetInt operator *(const SetInt& rtSide);  // Intersection
	SetInt operator -(const SetInt& rtSide);  // Set subtraction
	SetInt& operator =  (const SetInt& rtSide);  // Assignment
	// Avoid overloading =, copy constructor, destructor by
	//    assuming the data is contiguous

};
// End SetInt class

#endif  // SETINT
