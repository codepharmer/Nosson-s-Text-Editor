#pragma once

//this is the header file for the class called point 
//which contains two integer values and stores them as a point
//the class also contains setters and getters which allow 
//us to retreive information straight from Main
template <class TYPE>
class Point{
public:
	Point();
	
	Point(TYPE, TYPE);
	
	Point operator+(const Point&);

	Point operator=(const Point&);

	bool operator== (const Point&) const;

	void setX(TYPE);
	
	void setY(TYPE);
	
	TYPE getX() const;
	
	TYPE getY() const;
	
	TYPE distance(Point);
	//Point sumOfPoints(Point, Point);
	void display();
	//void placeCursorAt(Point);
private:
	TYPE mX;
	TYPE mY;
};

#include "Point.inl"
