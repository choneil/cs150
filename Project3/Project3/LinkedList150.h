#pragma once
#include<iostream>
#include<string>
using namespace std;


typedef int LinkedListElementType;

struct LinkedListNode; // prototype the node struct
typedef LinkedListNode* LLNodeptr; // nickname the 'node*' into 'nodeptr' to make it easier to use
struct LinkedListNode // define the node's structure
{
	LinkedListElementType data;
	LLNodeptr next;
};

class LinkedList150
{
private:
	LLNodeptr head;
public:
	LinkedList150();

	void insertAtHead(LinkedListElementType item);
	void insertAt(LinkedListElementType item, int position);
	void removeAtHead();
	void removeAt(int position);

	// make a function that returns how many nodes there are.
	int getSize() const;
	void printList(ostream& outstream) const;
	bool isEmpty() const;

	// make a function that clears the list by removing all nodes
	void clearList();

	//void printList(ostream& outstream) const;
	int removeAllDuplicates();
	void moveElementUp(int position);
	void moveElementDown(int position);
};
