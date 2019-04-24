#include "Xeditor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "BinarySearchTree.h"

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

void Xeditor::readfile(const string readThisFile) {
	ifstream keyWords;
	keyWords.open("keywords.txt");
	std::ifstream readLines;
	readLines.open(readThisFile);
	if (!readLines.is_open()) {
		std::cout << "An error has occurred. \nYour file did not open.";
		exit(0);
	}
	if (!keyWords.is_open()) {
		std::cout << "An error has occurred. \nYour file did not open.";
		exit(0);
	}
	std::string addThisLine;
	int linkedListIndex = 1;
	while (!keyWords.eof())
	{
		keyWords >> addThisLine;
		keyWordTree.add(addThisLine);
	}

	while (!readLines.eof())
	{

		getline(readLines, addThisLine, '\n');
		lines.insert(linkedListIndex, addThisLine);
		linkedListIndex++;
	}
	readLines.close();
}

void Xeditor::display(LinkedList<string> &lines) {
	if (!lines.isEmpty()) {
		int numberOfLines = lines.getLength();

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
					isKeyword = keyWordTree.contains(currentWord);
					if (isKeyword)
						colorText(FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);  //blue
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
	}
}

void Xeditor::display(string myLine) {
		bool isKeyword = false;
		// print indivudual line over last line
		int j = 0;
		for (int i = 0; i < myLine.size(); i++) {
			if (tolower(myLine[i]) >= 'a' && tolower(myLine[i]) <= 'z') {  //letter
				string currentWord;
				for (j = i; (tolower(myLine[j]) >= 'a' && tolower(myLine[j]) <= 'z'); j++) {
					currentWord += myLine[j];
				}
				isKeyword = keyWordTree.contains(currentWord);
				if (isKeyword)
					colorText(FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);  //blue
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
		placeCursorAt(cursorPosition);
	}
	
void Xeditor::insert() {
#define ESCAPE 27
#define BACKSPACE 8
#define ENTER '\r'

	char charInput = '\0';
	int zerothIndex = 0;
	Point<int> lineBeginning( zerothIndex, cursorPosition.getY());
	string currLine;
	if (lines.isEmpty()) {
		currLine = "";
		lines.insert(1, currLine);
	}
	else
		currLine = lines.getEntry(cursorPosition.getY() + 1);
	string tempString = "";
	Snapshot snapshotInI;
	int numLinesInserted = 0;
	bool lineEdited = false;
	bool notFirstInsert = false;
	while (!(charInput == ESCAPE)) {
		lineBeginning.setX(lineBeginning.getX() + 1);
		placeCursorAt(lineBeginning);
		charInput = _getch();
		tempString += charInput;
		//currentWord += charInput;
		if (tempString.size() == 1)
			currLine = lines.getEntry(cursorPosition.getY() + 1);
		lineBeginning.setY(cursorPosition.getY());
		placeCursorAt(lineBeginning);
		if (charInput == ENTER) {
			//currLine.insert(0, tempString);
			numLinesInserted++;
			snapshotInI.setLineOfTxt(tempString);
			snapshotInI.setPosition(cursorPosition);
			string command = "I";
			//char tempCharInt = '0';
			//tempCharInt += numLinesInserted;
			command += ('0' + numLinesInserted);
			snapshotInI.setCommand(command);
			//we don't want more than one snapshot of Insert stored,
			//so we pop the last one before adding this one
			if (notFirstInsert)
			undoStack.pop();
			undoStack.push(snapshotInI);
			lines.replace(cursorPosition.getY() + 1, currLine);
			lines.insert(cursorPosition.getY() + 1, tempString);
			notFirstInsert = true;
			charInput = NULL;
			tempString.clear();
			system("CLS");
			display(lines);
			int numberOfLinesInFile = lines.getLength();
			Point<int> printHere(0, numberOfLinesInFile + 2);
			placeCursorAt(printHere);
			std::cout << "\t-------INSERT--------\n";
			//we add 2 to the current Y position.
			//The first one is because Y values start at 1, the second is to move
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
					placeCursorAt(tempPoint);
					cout <<" ";
					tempPoint.setX(SPACES_IN_MARGIN);
					placeCursorAt(tempPoint);
					//cout << tempString << currLine ;
					string editedLine = tempString + currLine;
					lines.replace(cursorPosition.getY() + 1, editedLine );
					// '\0' at the end of tempString swallows the last char 
					tempPoint.setX(SPACES_IN_MARGIN + editedLine.length() + 1);
					placeCursorAt(tempPoint);
					cout << " ";
					tempPoint.setX(SPACES_IN_MARGIN);
					placeCursorAt(tempPoint);
					display(editedLine);
					if (cursorPosition.getX() > SPACES_IN_MARGIN)
					cursorPosition.setX(cursorPosition.getX() -1);
					placeCursorAt(cursorPosition);
				};
			}
			else {
				cursorPosition.setX(tempString.size());
				placeCursorAt(cursorPosition);
				lines.replace(cursorPosition.getY() + 1, tempString + currLine); 
				lineBeginning.setX(SPACES_IN_MARGIN);
				lineBeginning.setY(cursorPosition.getY());
				placeCursorAt(lineBeginning);
				display(lines.getEntry(cursorPosition.getY() + 1));
			}
			lineEdited = true;
		}
	}
	if (charInput == ESCAPE) {
		if (lineEdited) {
			//currLine = lines.getEntry(cursorPosition.getY() + 1);
			snapshotInI.setLineOfTxt(currLine);
			if (tempString == "\x1b") {
				lines.replace(cursorPosition.getY() + 1, currLine);
			}
			snapshotInI.setPosition(cursorPosition);
			snapshotInI.setCommand("i");
			//undoStack.push(snapshotInI);
			charInput = NULL;
		}
	}
		//display lines after each change
		system("CLS");
		display(lines);
		placeCursorAt(lineBeginning);
	}
	
	bool Xeditor::undo(stack<Snapshot> &undoStack) {
		bool undidStuff = false;
		if (!undoStack.empty())
		{
			undidStuff = true;
			//first pop off what we just stored

			Snapshot restoreThisVersion;
			restoreThisVersion = undoStack.top();
			char undoCmd = restoreThisVersion.getCommand()[0];
			char undoCmd1 = restoreThisVersion.getCommand()[1];
			undoStack.pop();
			//cursorPosition = restoreThisVersion.getPosition();
			cursorPosition.setX(restoreThisVersion.getPosition().getX());
			cursorPosition.setY(restoreThisVersion.getPosition().getY());
			switch (undoCmd) {

			case ('d'):
				lines.insert(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
				break;
			case ('x'):
				lines.replace(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
				break;
			case ('I'):
				for (int i = 0; i < (undoCmd1 - '0'); i++) {
					lines.remove(cursorPosition.getY() + 1);
					if (cursorPosition.getY() > 0)
					cursorPosition.setY(cursorPosition.getY() - 1);
				}
				break;
			case ('i'):
				lines.replace(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
				break;
			default:
				break;
			}

			//lines.clear();
		}
		else
		{
			int numberOfLinesInFile = lines.getLength();
			Point<int> printHere(0, numberOfLinesInFile + 2);
			placeCursorAt(printHere);
			std::cout << "\tNothing left to undo.\n";
		}
	return undidStuff;
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
	string currCommand = "";
	int lineToEdit;
	int charToRemove;
	bool stuffChanged = false; 
	string currLine;
	do {
		if (!lines.isEmpty())
		currLine = lines.getEntry(cursorPosition.getY()+1);
		currCommand.clear();
		command = _getch();
		currCommand += command;
		Snapshot cacheSnapshot(cursorPosition, currLine, currCommand );
		switch (command)
		{
		case('j'):
			if (!lines.isEmpty()) {
				lengthOfLine = (cursorPosition.getY() + 1) % lines.getLength();
				//cursorYVal = cursorPosition.getY();
				if (cursorPosition.getY() < lengthOfLine)
					cursorPosition.setY(cursorPosition.getY() + 1);
			}
			break;
		case('l'):
			if (!lines.isEmpty())
			lengthOfLine = lines.getEntry(cursorPosition.getY() + 1).length();
			if (cursorPosition.getX() < lengthOfLine + SPACES_IN_MARGIN - ZERO_INDEX)
				cursorPosition.setX(cursorPosition.getX() + 1);
			break;
		case('k'):
			if (cursorPosition.getY() > 0)
				cursorPosition.setY(cursorPosition.getY() - 1);
			break;
		case('h'):
			if ((cursorPosition.getX() - SPACES_IN_MARGIN) > 0) 
				cursorPosition.setX(cursorPosition.getX() - 1);
			break;
		case('d'):
			currLine.clear();
			command = _getwch();
			if (command == 'd') {
				currCommand += command;
				cacheSnapshot.setCommand(currCommand);
				if (!lines.isEmpty())
				undoStack.push(cacheSnapshot);
				int numberOfLines = lines.getLength();
				if (numberOfLines >  1) {
					lines.remove((cursorPosition.getY() + 1));
					stuffChanged = true;
				}
				else if (numberOfLines == 1) {
					lines.remove((cursorPosition.getY() + 1));
					//we don't want to call display when (lines.isEmpty())
					system("CLS");
					stuffChanged = false;
				}
				if (cursorPosition.getY() > 0) {
					cursorPosition.setY(cursorPosition.getY() - 1);
				}
				
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
			stuffChanged = undo(undoStack);
			currCommand.clear();
				break;
		case ('I'): {
			//reference undoStack in insert to save when changes are made
			Point<int> placeHolder(cursorPosition.getX(), cursorPosition.getY());
			insert();
			//placeCursorAt(placeHolder);
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
