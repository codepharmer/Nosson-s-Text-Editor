#pragma once
#include "LinkedList.h"
#include "Point.h"
#include "Snapshot.h"
#include <stack>
#include <cstdlib>
class Xeditor {

	private:
	LinkedList<std::string> lines;
	Point<int> cursorPosition;
	stack<Snapshot> undoStack;

	public:
	Xeditor();
	void readfile(const std::string);
	void display(LinkedList<std::string>&);
	void run();
	void insert(stack<Snapshot> &, Point<int> &);
};
