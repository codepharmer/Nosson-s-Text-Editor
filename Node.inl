//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.cpp
Listing 4-2 */
#include "Node.h"

template<class TYPE>
Node<TYPE>::Node() : next(nullptr)
{
} // end default constructor

template<class TYPE>
Node<TYPE>::Node(const TYPE& anItem) : item(anItem), next(nullptr)
{
} // end constructor

template<class TYPE>
Node<TYPE>::Node(const TYPE& anItem, Node<TYPE>* nextNodePtr) :
item(anItem), next(nextNodePtr)
{
} // end constructor

template<class TYPE>
void Node<TYPE>::setItem(const TYPE& anItem)
{
	item = anItem;
} // end setItem

template<class TYPE>
void Node<TYPE>::setNext(Node<TYPE>* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

template<class TYPE>
TYPE Node<TYPE>::getItem() const
{
	return item;
} // end getItem

template<class TYPE>
Node<TYPE>* Node<TYPE>::getNext() const
{
	return next;
} // end getNext
