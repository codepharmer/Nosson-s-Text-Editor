//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.h
Listing 4-1 */
#ifndef NODE_
#define NODE_

template<class TYPE>
class Node
{
private:
	TYPE        item; // A data item
	Node<TYPE>* next; // Pointer to next node

public:
	Node();
	Node(const TYPE& anItem);
	Node(const TYPE& anItem, Node<TYPE>* nextNodePtr);
	void setItem(const TYPE& anItem);
	void setNext(Node<TYPE>* nextNodePtr);
	TYPE getItem() const;
	Node<TYPE>* getNext() const;
}; // end Node

#include "Node.inl"
#endif