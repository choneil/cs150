#include "LinkedList150.h"
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

LinkedList150::LinkedList150()
{
	head = nullptr;
}

void LinkedList150::insertAtHead(LinkedListElementType item)
{
	LLNodeptr temp = new LinkedListNode;
	temp->data = item;
	temp->next = head;
	head = temp;
}

void LinkedList150::insertAt(LinkedListElementType item, int position)
{
	if (position < 0)
		throw exception("insertAt() recieved a negative position");
	if (position == 0)
	{
		insertAtHead(item);
		return;
	}
	int currentLocation = 0;
	LLNodeptr temp = head;
	while ((temp != nullptr) && (currentLocation < (position - 1)))
	{
		currentLocation++;
		temp = temp->next;
	}
	if (temp == nullptr)
		throw exception("insertAt() recieved a position that is too big");
	LLNodeptr newNode = new LinkedListNode;
	newNode->data = item;
	newNode->next = temp->next;
	temp->next = newNode;
}

void LinkedList150::removeAtHead()
{
	if (isEmpty())
		throw exception("removeAtHead() called on an empty list");
	LLNodeptr temp = head;
	head = head->next;
	delete temp;
}

void LinkedList150::removeAt(int position)
{
	if (position < 0)
		throw exception("removeAt() recieved a negative position");
	if (position == 0)
	{
		removeAtHead();
		return;
	}
	int currentLocation = 0;
	LLNodeptr temp = head;
	while ((temp != nullptr) && (currentLocation < (position - 1)))
	{
		currentLocation++;
		temp = temp->next;
	}
	if ((temp == nullptr) || (temp->next == nullptr))
		throw exception("removeAt() recieved a position that is too big");
	LLNodeptr deletePtr = temp->next; // point at the node to remove
	temp->next = deletePtr->next; // bypass the node to remove
	delete deletePtr; // remove the node to remove
}

// make a function that returns how many nodes there are.
int LinkedList150::getSize() const
{
	LLNodeptr temp = head;
	int count = 0;
	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

bool LinkedList150::isEmpty() const
{
	return head == nullptr;
}

void LinkedList150::clearList()
{
	LLNodeptr temp = head;
	while (head != nullptr)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}

int LinkedList150::removeAllDuplicates() {
	LLNodeptr currentPtr;
	LLNodeptr searchPtr;
	LLNodeptr deletePtr;
	LLNodeptr trailingPtr;
	int deleted_total = 0;
	int deleted_value = 0;
	currentPtr = head;
	
	while (currentPtr != nullptr) {
		searchPtr = currentPtr->next;
		trailingPtr = currentPtr;
		deleted_value = 0;
		while (searchPtr != nullptr) {
			if (searchPtr->data == currentPtr->data) {
				trailingPtr->next = searchPtr->next;
				deletePtr = searchPtr;
				delete deletePtr;
				deleted_total++;
				deleted_value++;
				searchPtr = trailingPtr->next;
			}
			else {
				
				searchPtr = searchPtr->next;
				trailingPtr = trailingPtr->next;
			}
			
		}
		cout << "Deleted " << currentPtr->data << "(s): " << deleted_value << endl;
		currentPtr = currentPtr->next;
		
	}
	return deleted_total;
}

void LinkedList150::moveElementUp(int position) {
	LLNodeptr object;
	LLNodeptr target;
	LLNodeptr back;
	
	int curr_pos = 0;
	if (position <= 0)
		throw invalid_argument("no.");

	if (position == 1) {
		LLNodeptr target = head;
		LLNodeptr object = head->next;
		LLNodeptr back = object->next;
		head = object;
		object->next = target;
		target->next = back;
	}
	else {
		LLNodeptr current = head;

		while (curr_pos != position - 2)
		{
			current = current->next;
			curr_pos++;
		}
		LLNodeptr target = current->next;
		if(target->next == nullptr){
			throw invalid_argument("node position outofrange");
			return;
		}
		
		LLNodeptr object = target->next;
		
		if (object->next == nullptr) {
			target->next = nullptr;
			object->next = target;
			current->next = object;
		}else{
		LLNodeptr back = object->next;

		target->next = back;
		object->next = target;
		current->next = object;
		}

	}
}

void LinkedList150::moveElementDown(int position) {
	int curr_pos = 0;
	if (position == 0){
		LLNodeptr target = head;
		LLNodeptr object = target->next;
		LLNodeptr back = object->next;
		head = object;
		head->next = target;
		target->next = back;
		return;
	}
	if (position < 0) {
		throw invalid_argument("no.");
	}
	else {
		LLNodeptr current = head;

		while (curr_pos != position - 1)
		{	
			
			current = current->next;
			curr_pos++;
		}
		
		if (current->next == nullptr)
			throw invalid_argument("node not in list.");
		LLNodeptr target = current->next;
		if (target->next == nullptr)
			throw invalid_argument("cannot move node down any further.");
		LLNodeptr object = target->next;
		if (object->next == nullptr) {
			current->next = object;
			object->next = target;
			target->next = nullptr;
		}
		else {
			LLNodeptr back = object->next;
			
			target->next = back;
			object->next = target;
			current->next = object;
		}

	}
}

void LinkedList150::printList(ostream& outstream) const
{
	int size = getSize();
	string label1 = "Position: ";
	string label2 = "Value:    ";
	int width = label1.length() + ((1 + size) * 4);
	outstream << setw(width) << setfill('-') << "" << endl;
	outstream << setw(label1.size() + 4) << setfill(' ') << label1 << left;
	LLNodeptr temp = head;
	int position = 0;
	while (temp != nullptr)
	{
		outstream << setw(4) << setfill(' ') << left <<  position;
		temp = temp->next;
		position++;
	}
	outstream << endl;
	outstream << setw(width) << setfill('-') << "" << endl;
	outstream << setw(label2.size() + 4) << setfill(' ') << label2 << left;
	temp = head;

	while (temp != nullptr)
	{
		outstream << setw(4) << setfill(' ') << left << temp->data;
		temp = temp->next;
	}
	outstream << endl;
	outstream << setw(width) << setfill('-') << "" << endl;
	outstream << "Size: " << size << endl;
}

