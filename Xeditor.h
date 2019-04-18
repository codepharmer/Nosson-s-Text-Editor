#pragma once
#include "LinkedList.h"
#include "Point.h"
#include "Snapshot.h"
#include <stack>
#include <cstdlib>
#include <memory>
#include "BinarySearchTree.h"
class Xeditor {

	private:
	LinkedList<std::string> lines;
	Point<int> cursorPosition;
	stack<Snapshot> undoStack;
	BinarySearchTree<string> keyWordTree;

	public:
	Xeditor();
	void readfile(const std::string);
	void display(LinkedList<std::string>&);
	void display(std::string);
	bool undo(stack<Snapshot>&);
	void run();
	void insert();
};
