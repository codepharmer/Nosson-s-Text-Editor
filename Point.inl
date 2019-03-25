#include "Point.h"
#include <iostream>
#include <string>
#include <cmath>
#include "windows.h"
#include<conio.h>
#include <cstddef>



//in this file we define Point constructors and methods
//to determine the distance between two points a and b  
	//method use a method that takes in

	

template <class TYPE>
Point<TYPE>::Point() { //define constructers 
	mY = mX = 0;

}
template <class TYPE>
Point<TYPE>::Point(TYPE inx, TYPE iny)
{
	setX(inx);
	setY(iny);
}

template <class TYPE>
Point<TYPE>  Point<TYPE>::operator+ (const Point<TYPE>& pointToAdd)
{
	Point<TYPE> addPoints;
	addPoints.mX= mX + pointToAdd.mX;
	addPoints.mY= mY + pointToAdd.mY;
	return addPoints;
}

template <class TYPE>
bool Point<TYPE>::operator== (const Point<TYPE> & secondPoint) const
{
	if (mX == secondPoint.mX &&
		mY == secondPoint.mY)
		return true;
	else
		return false;
}
template <class TYPE>
void Point<TYPE>::setX(TYPE inX)
{
	mX = inX;
}
template <class TYPE>
void Point<TYPE>::setY(TYPE inY)
{
	mY = inY;
}
template <class TYPE>
TYPE Point<TYPE>::getX() const
{
	return mX;
}
template <class TYPE>
TYPE Point<TYPE>::getY() const
{
	return mY;
}
//returns the distance between a given point and a point p2 sent to it
template <class TYPE>
TYPE Point<TYPE>::distance(Point<TYPE> p2)
{
	return sqrt((mX - p2.mX)*(mX - p2.mX) + (mY - p2.mY)*(mY - p2.mY));
}
template <class TYPE>
void Point<TYPE>::display()
{
	std::cout << "(" << mX << "," << mY << ")";
}
