#include "MazeSearcher.h"
#include <iostream>
#include <string>
using namespace std;
#include "MazeGenerator.h"

typedef MazeCell* elementType;

MazeSearcher::MazeSearcher()
{
	listSize = 0;
	capacity = DEFAULT_CAPACITY;
	list = new elementType[DEFAULT_CAPACITY];
	head = nullptr;
	tail = nullptr;
}

void MazeSearcher::insert(elementType element, int position) {
	if ((position < 0) || (position > listSize))
		throw invalid_argument("insert() received an invalid position");
	if (isFull())
	{
		capacity += DEFAULT_CAPACITY;
		elementType* temp = new elementType[capacity];
		for (int i = 0; i < listSize; i++) {
			temp[i] = list[i];
			delete[] list;
		}
		list = temp;
	}
	for (int i = listSize; i > position; i--)
		list[i] = list[i - 1];
	list[position] = element;
	if (position == 0)
		head = replaceHead(element);
	if (position == listSize)
		tail = element;
	listSize++;
}

void MazeSearcher::removeAt(int position)
{
	if ((position < 0) || (position >= listSize))
		throw invalid_argument("removeAt() received an invalid position.");
	for (int i = position;(i < (listSize + 1)); i++)
		list[i] = list[i + 1];
	listSize--;
}

void MazeSearcher::printList() const
{
	for (int i = 0; i < listSize; i++)
	{
		cout << i << ": " << list[i] << endl;
	}
}

int MazeSearcher::getListSize() const
{
	return listSize;
}

int MazeSearcher::getCapacity() const
{
	return capacity;
}

void MazeSearcher::clearList()
{
	listSize = 0;
}

bool MazeSearcher::isFull() const
{
	return(listSize == capacity);
}

bool MazeSearcher::isEmpty() const
{
	return(listSize == 0);
}

elementType MazeSearcher::retrieve(int position) const
{
	if((position <0)||(position>= listsize))
		throw invalid_argument("retreive() received an invalid position.");
	return list[position];
}

void replaceHead(elementType* newHead) {
	head = newHead;
}

void replaceTail(elementType* newTail) {
	tail = newTail;
}

void MazeSearcher::insertAtHead(elementType* newElement) {
	
}

void MazeSearcher::push(elementType* newElement) {
	insert(newElement, 0);
}

void MazeSearcher::pop() {
	removeAt(0);
}