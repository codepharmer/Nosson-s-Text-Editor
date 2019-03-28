#include "Xeditor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

Xeditor::Xeditor() {
}

void placeCursorAt(Point<int> inCoordinate) {
	COORD coord;
	coord.X = inCoordinate.getX();
	coord.Y = inCoordinate.getY();
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}

void Xeditor::display(LinkedList<std::string> &lines, int &numberOfLines)
{
	numberOfLines = lines.getLength();
	for (int i = 1; i <= numberOfLines; i++)
	{
		std::string printThisLine;
		printThisLine = lines.getEntry(i);
		std::cout << "~ " << printThisLine << "\n";
	}
}

void Xeditor::readfile(const std::string readThisFile)
{

	std::ifstream readLines;
	readLines.open(readThisFile);
	if (!readLines.is_open()) {
		std::cout << "An error has occurred. \nYour file did not open.";
		exit(0);
	};
	std::string addThisLine;
	int linkedListIndex = 1;

	while (!readLines.eof()) {
		getline(readLines, addThisLine, '\n');
		lines.insert(linkedListIndex, addThisLine);
		linkedListIndex++;
	}
	readLines.close();

}



void Xeditor::run()
{
	//print txt file to screen

	int numberOfLines;
	display(lines, numberOfLines);
	const int SPACES_IN_MARGIN = 2;
	const int ZERO_INDEX = 1;
	cursorPosition.setX(cursorPosition.getX() + SPACES_IN_MARGIN);
	placeCursorAt(cursorPosition);
	bool continueEditing = true;
	//std::string * currLine;
	//start the editing part of the editor
	
	char command;
	int lengthOfLine;
	int cursorYVal;
	int cursorXVal;
	string currCommand = "";
	int lineToEdit;
	int charToRemove;
	bool stuffChanged = false;
	do {
		
		// = lines.getEntry(cursorPosition.getY());
			string currLine = lines.getEntry(cursorPosition.getY()+1);
			std::string babababab;
			int updatePosition;
		currCommand.clear();
		command = _getch();
		currCommand += command;
		Snapshot cacheSnapshot(cursorPosition, currLine, currCommand );
		switch (command)
		{
		case('k'):

			lengthOfLine = (cursorPosition.getY() + 1) % lines.getLength();
			cursorYVal = cursorPosition.getY();
			if (cursorYVal < lengthOfLine)
			{
				cursorYVal++;
				cursorPosition.setY(cursorYVal);
			}
			break;
		case('l'):
			cursorXVal = cursorPosition.getX();
			lengthOfLine = lines.getEntry(cursorPosition.getY() + 1).length();
			if (cursorXVal < lengthOfLine + SPACES_IN_MARGIN - ZERO_INDEX)
			{
				updatePosition = (cursorPosition.getX() + 1);
				cursorPosition.setX(updatePosition);
			}
			break;
		case('j'):
			if (cursorPosition.getY() > 0) {
				cursorYVal = cursorPosition.getY() - 1;
				cursorPosition.setY(cursorYVal);
			}
			break;
		case('h'):
			if ((cursorPosition.getX() - SPACES_IN_MARGIN) > 0) {
				cursorYVal = cursorPosition.getX() - 1;
				cursorPosition.setX(cursorYVal);
			}
			break;
		case('d'):

			currLine.clear();
			command = _getwch();
			if (command == 'd'){
			currCommand += command;
			cacheSnapshot.setCommand(currCommand);
			undoStack.push(cacheSnapshot);

			//removes whichever line cursor is at
			//y-values are really offsets, they start at 0, so we add 1 to the y value t
			if (numberOfLines > 1) {
				lines.remove((cursorPosition.getY() + 1));
			}
			else{
 			lines.insert(numberOfLines, "" );
			lines.remove(numberOfLines + 1);
			}
			if (cursorPosition.getY() > 0) {
				cursorPosition.setY(cursorPosition.getY() - 1);
			}
			stuffChanged = true;
		}
			break;
		case('x'):
			lineToEdit = cursorPosition.getY() + 1;
			charToRemove = cursorPosition.getX() + SPACES_IN_MARGIN;
			&currLine.erase(charToRemove, 1);
			//currLine[charToRemove] = '\b';
			lines.replace(lineToEdit, currLine);
			stuffChanged = true;
			break;
		case('u'):
			if (!undoStack.empty())
			{
				//first pop off what we just stored
					currCommand.clear();
					Snapshot restoreThisVersion;
					restoreThisVersion = undoStack.top();
					currCommand = restoreThisVersion.getCommand();
					undoStack.pop();
					cursorPosition = restoreThisVersion.getPosition();
					if (currCommand == "dd"){
						lines.insert(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
					}
					else if (currCommand == "x"){
					}

					//lines.clear();
					
					stuffChanged = true;
					//undoStack.pop();
				/*	currLine.erase(5, 0);
					lines.replace(cursorPosition.getX(), currLine );*/
				}
			else
				{
				/*std::cout << "Error! Undostack is empty; can't pop.\n";
				system("PAUSE");
				exit(0);*/
				int numberOfLinesInFile = lines.getLength();
				Point<int> printHere(0, numberOfLinesInFile + 2);
				placeCursorAt(printHere);
				std::cout << "Error! Undostack is empty; can't pop.\n";
				}
				 
		

				break;
		default:
			/*Point<int> printOutputHere(0, lines.getLength() + 5);
			placeCursorAt(printOutputHere);
			std::cout << "Would you like to continue editing?\n"
				<< "0 for no, 1 for yes";
			std::cin >> continueEditing;*/
			break;
		}
			
		//clear screen and print current lines
		if (stuffChanged){
			system("CLS"); 
			display(lines, numberOfLines);
			stuffChanged = false;
		}
		//done printing lines
		//shift cursor over to 
		if (cursorPosition.getX() == 0)
			cursorPosition.setX(cursorPosition.getX() + SPACES_IN_MARGIN);
		placeCursorAt(cursorPosition);
	} while (command != 'q');

	//finish the editing part of the editor

	//write new line of strings to file


}