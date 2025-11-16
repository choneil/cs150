#include<iostream>
#include<ctime>
#include<string>
#include "LinkedList150.h"
using namespace std;

const string UP = "up";
const string DOWN = "down";

void shiftSomeElements(LinkedList150 &myList, string upOrDown);
void shiftOneElement(LinkedList150 &myList, int position, void (LinkedList150::*shiftFunction)(int), string upOrDown);

int main()
{
	LinkedList150 myList;
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 16; i++)
		myList.insertAtHead(rand() % 10);
	cout << "Starting list:\n";
	myList.printList(cout);
	cout << "Removing Duplicates:\n";
	cout << "Removed " << myList.removeAllDuplicates() << " duplicates.\n";
	cout << "List after duplicates are removed:\n";
	myList.printList(cout);
	shiftSomeElements(myList, UP);
	shiftSomeElements(myList, DOWN);
	cout << "\nFinal list:\n";
	myList.printList(cout);
	return 0;
}

void shiftSomeElements(LinkedList150 &myList, string upOrDown)
{
	cout << "\n    Shifting " << upOrDown << ":\n";
	void (LinkedList150:: * shiftFunction)(int);
	shiftFunction = (upOrDown == UP) ? &LinkedList150::moveElementUp : &LinkedList150::moveElementDown;
	shiftOneElement(myList, -1, shiftFunction, upOrDown);
	myList.printList(cout);
	shiftOneElement(myList, 0, shiftFunction, upOrDown);
	myList.printList(cout);	
	shiftOneElement(myList, myList.getSize()-1, shiftFunction, upOrDown);
	myList.printList(cout);
	shiftOneElement(myList, myList.getSize(), shiftFunction, upOrDown);
	myList.printList(cout);
	for (int i = 0; i < 10; i++)
	{
		shiftOneElement(myList, (rand() % myList.getSize()), shiftFunction, upOrDown);
		myList.printList(cout);
	}
}

void shiftOneElement(LinkedList150 &myList, int position, void (LinkedList150::*shiftFunction)(int), string upOrDown)
{
	cout << "\nShifting position " << position << " " << upOrDown << ": ";
	try {
		((myList.*shiftFunction) (position));
		cout << "success!\n";
	}
	catch (invalid_argument e)
	{
		cout << "failed!\n";
	}
}
