#include "Xeditor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


const int SPACES_IN_MARGIN = 1;

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
void colorText(int value) {

	//COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value);

}
void Xeditor::display(LinkedList<string> &lines)
{
	int numberOfLines = lines.getLength();/*
	for (int i = 1; i <= numberOfLines; i++)
	{
		string printThisLine;
		printThisLine = lines.getEntry(i);
		std::cout << "~" << printThisLine << "\n";
	}*/

	bool isKeyword;
	string myLine;
	for (int k = 1; k < numberOfLines + 1; k++) {
		myLine = lines.getEntry(k);
		int j = 0;
		// print without 'words'
		cout << '~';
		for (int i = 0; i < myLine.size(); i++) {
			if (tolower(myLine[i]) >= 'a' && tolower(myLine[i]) <= 'z') {  //letter
				string currentWord;
				for (j = i; (tolower(myLine[j]) >= 'a' && tolower(myLine[j]) <= 'z'); j++) {
					currentWord += myLine[j];
				}
				isKeyword = !keyWordTree.contains(currentWord);
				if (isKeyword)
					colorText(11 + 15 * 16);  //blue
				else
					colorText(0XF0);
				cout << currentWord;
				if (j != 0)
					i = j - 1;
			}
			else
				cout << myLine[i];
			//if (i >= myLine.size()-1) 
			// cout << endl;
		}
		cout << endl;

	}
	placeCursorAt(cursorPosition);
	//if (inInsertMode)
	//placeCursorAt the bottomof the screen and cout<< blabala insert mode..
	//if 

}
	

void Xeditor::insert() {
#define ESCAPE 27
#define BACKSPACE 8
#define ENTER '\r'

	char charInput = '\0';
	int zerothIndex = 0;
	Point<int> lineBeginning( zerothIndex, cursorPosition.getY() + 1);
	string currLine = lines.getEntry(cursorPosition.getY() + 1);
	string tempString = "";
	Snapshot snapshotInI;
	bool lineEdited = false;

	while (!(charInput == ESCAPE)) {
		currLine = lines.getEntry(cursorPosition.getY() + 1);
		lineBeginning.setX(lineBeginning.getX() + 1);
		lineBeginning.setY(cursorPosition.getY());
		placeCursorAt(lineBeginning);
		charInput = _getch();
		tempString += charInput;
		lineBeginning.setY(cursorPosition.getY() + 1);
		placeCursorAt(lineBeginning);
		if (charInput == ENTER) {
			//currLine.insert(0, tempString);
			snapshotInI.setLineOfTxt(tempString);
			snapshotInI.setPosition(cursorPosition);
			snapshotInI.setCommand("\n");
			undoStack.push(snapshotInI);
			lines.insert( cursorPosition.getY() + 1, tempString );
			charInput = NULL;
			tempString.clear();
			system("CLS");
			display(lines);
			cursorPosition.setY(cursorPosition.getY() + 1);
			cursorPosition.setX(SPACES_IN_MARGIN);
			lineBeginning.setX(zerothIndex);
			placeCursorAt(cursorPosition);
			snapshotInI.setLineOfTxt(currLine);
			currLine = lines.getEntry(cursorPosition.getY() + 1);
			lineEdited = false;
		}
		else{
			if (charInput == BACKSPACE) {
				if (tempString.size() > 1) {//it is already holding the carriage return, so the size is at least 1
					Point<int> tempPoint( tempString.size() - 1 + currLine.size() , cursorPosition.getY());
					tempString.erase(tempString.size() - 2, 2);
					lineBeginning.setX(lineBeginning.getX() - 2);
					placeCursorAt( tempPoint );
					cout <<" ";
					tempPoint.setX(SPACES_IN_MARGIN);
					placeCursorAt(tempPoint);
					cout << tempString << currLine ;
					currLine = lines.getEntry(cursorPosition.getY() + 1);
				};
			}
			else {
				cursorPosition.setX(tempString.size());
				placeCursorAt(cursorPosition);
				cout << charInput << currLine;
			}
			lineEdited = true;
		}
	}
	if (charInput == ESCAPE) {
		if (lineEdited) {
			currLine = lines.getEntry(cursorPosition.getY() + 1);
			snapshotInI.setLineOfTxt(currLine);
			char fillNullAtEndOfTempString = '0';
			currLine = tempString + fillNullAtEndOfTempString + currLine;
			lines.replace(cursorPosition.getY() + 1, currLine);
			snapshotInI.setPosition(cursorPosition);
			snapshotInI.setCommand("I");
			undoStack.push(snapshotInI);
		}
	}
		//display lines after each change
		system("CLS");
		display(lines);
		placeCursorAt(lineBeginning);
	}
	
	



void Xeditor::readfile(const string readThisFile)
{
	std::ifstream readLines;
	readLines.open(readThisFile);
	if (!readLines.is_open()) {
		std::cout << "An error has occurred. \nYour file did not open.";
		exit(0);
	};
	string addThisLine;
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
	display(lines);
	const int ZERO_INDEX = 1;
	cursorPosition.setX(cursorPosition.getX() + SPACES_IN_MARGIN);
	placeCursorAt(cursorPosition);
	bool continueEditing = true;
	//string * currLine;
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
			string babababab;
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
			if (command == 'd') {
				currCommand += command;
				cacheSnapshot.setCommand(currCommand);
				undoStack.push(cacheSnapshot);

				//removes whichever line cursor is at
				//y-values are really offsets, they start at 0, so we add 1 to the y value t
				int numberOfLines = lines.getLength();
				if (numberOfLines > 1) {
					lines.remove((cursorPosition.getY() + 1));
				}
				else {
					lines.insert(numberOfLines, "");
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
			charToRemove = cursorPosition.getX() - SPACES_IN_MARGIN;
			if (currLine[charToRemove] >= ' ') {
			currLine.erase(charToRemove, 1);
			undoStack.push(cacheSnapshot);
			}
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
					char undoCommand = restoreThisVersion.getCommand()[0];
					undoStack.pop();
					cursorPosition = restoreThisVersion.getPosition();
					switch ( undoCommand ) {

					case ('d'): 
							lines.insert(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
						break;
					case ('x'):
							currCommand.clear();
							lines.replace(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
						break;
					case ('\n'):
							lines.remove(cursorPosition.getY() + 1);
						break;
					case ('I'):
							lines.replace(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
						break;
					default:
						break;
					}

					//lines.clear();
					
					stuffChanged = true;
				}
			else
				{
				int numberOfLinesInFile = lines.getLength();
				Point<int> printHere(0, numberOfLinesInFile + 2);
				placeCursorAt(printHere);
				std::cout << "\tNothing left to undo.\n";
				}
				 
		

				break;
		case ('I'): {
			//reference undoStack in insert to save when changes are made
			Point<int> placeHolder = cursorPosition;
			insert();
			placeCursorAt(placeHolder);
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
			display(lines);
			stuffChanged = false;
		}
		//done printing lines
		//shift cursor over to 
		if ( cursorPosition.getX() == 0 )
			cursorPosition.setX(cursorPosition.getX() + SPACES_IN_MARGIN);
		placeCursorAt(cursorPosition);
	} while (command != 'q');

	//finish the editing part of the editor

	//write new line of strings to file


}
