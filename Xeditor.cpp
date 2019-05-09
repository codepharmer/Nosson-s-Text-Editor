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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value);

}

void Xeditor::readfile(string const readThisFile) {
	//cout << readThisFile << endl;
	ifstream keyWords;
	keyWords.open("keywords.txt");
	std::ifstream readLines;
	readLines.open(readThisFile);
	if (!readLines.is_open()) {
	 cout << "An error has occurred. \nYour file " << readThisFile << " did not open.\n";
		exit(0);
	}
	if (!keyWords.is_open()) {
		std::cout << "An error has occurred. \nYour keywords file did not open.";
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
	static const int TILDA_COLOR = 248;
	if (!lines.isEmpty()) {
		int numberOfLines = lines.getLength();

		bool isKeyword;
		string myLine;
		for (int k = 1; k < numberOfLines + 1; k++) {
			myLine = lines.getEntry(k);
			int j = 0;
			// print tildas with a distinct color (mean to look like vi editor)
			colorText(TILDA_COLOR);
			cout << '~';
			colorText(0XF0);
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

	int numberOfLinesInFile = lines.getLength();
	Point<int> printHere(0, numberOfLinesInFile + 2);
	placeCursorAt(printHere);
	std::cout << "\t-------INSERT--------\n";

	char charInput = '\0';
	int zerothIndex = 0;
	Point<int> lineBeginning( zerothIndex, cursorPosition.getY());
	string currLine;
	//if the linked-list "lines" is empty and we try to access a line we'll get an error
	if (lines.isEmpty()) {
		currLine = "";
		lines.insert(1, currLine);
	}
	else
		currLine = lines.getEntry(cursorPosition.getY() + 1);
	string tempString = "";
	Snapshot snapshotInI;
	snapshotInI.setLineOfTxt(currLine);
	snapshotInI.setPosition(cursorPosition);
	int numLinesInserted = 0;
	bool lineEdited = false;
	bool linesAdded = false;
	lineBeginning.setX(lineBeginning.getX() + 1);
	placeCursorAt(lineBeginning);
	while (!(charInput == ESCAPE)) {
		charInput = _getwch();
		tempString += charInput;
		//currentWord += charInput;
		if (tempString.size() == 1)
			currLine = lines.getEntry(cursorPosition.getY() + 1);
		lineBeginning.setY(cursorPosition.getY());
		placeCursorAt(lineBeginning);
		if (charInput == ENTER) {
			numLinesInserted++;
			snapshotInI.setLineOfTxt(tempString);
			snapshotInI.setPosition(cursorPosition);
			string command = "I";
			command += ('0' + numLinesInserted);
			snapshotInI.setCommand(command);
			//we don't want more than one snapshot of Insert stored,
			//so we pop the last one before adding this one
			if (linesAdded)
			undoStack.pop();
			undoStack.push(snapshotInI);
			lines.replace(cursorPosition.getY() + 1, currLine);
			lines.insert(cursorPosition.getY() + 1, tempString);
			linesAdded = true;
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
				cursorPosition.setX(cursorPosition.getX() + 1);
				lines.replace(cursorPosition.getY() + 1, tempString + '0' + currLine); 
				lineBeginning.setX(SPACES_IN_MARGIN);
				lineBeginning.setY(cursorPosition.getY());
				placeCursorAt(lineBeginning);
				display(tempString + currLine);
				placeCursorAt(cursorPosition);
			}
			lineEdited = true;
		}
	}
	if (charInput == ESCAPE) {
		if (!linesAdded) {
			snapshotInI.setCommand("I~");
			undoStack.push(snapshotInI);
		}
		if (lineEdited) {
			//currLine = lines.getEntry(cursorPosition.getY() + 1);
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
			int numberOfUndos = 1;
			Snapshot restoreThisVersion;
			restoreThisVersion = undoStack.top();
			char undoCmd = restoreThisVersion.getCommand()[0];
			char undoCmd1 = restoreThisVersion.getCommand()[1];
			undoStack.pop();
			//cursorPosition = restoreThisVersion.getPosition();
			cursorPosition.setX(restoreThisVersion.getPosition().getX());
			cursorPosition.setY(restoreThisVersion.getPosition().getY());
			//if (undoCmd > '1' && undoCmd <= '9') {
				numberOfUndos = undoCmd - '0';
			//}
			undoCmd = undoCmd1;
			
			while (numberOfUndos > 0) {
				
				
				switch (undoCmd) {
				case ('d'):
					lines.insert(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
					numberOfUndos--;
					while (numberOfUndos > 0) {
						//cursorPosition.setX(restoreThisVersion.getPosition().getX());
						restoreThisVersion = undoStack.top();
						cursorPosition.setY(restoreThisVersion.getPosition().getY() + 1);
						lines.insert(cursorPosition.getY(), restoreThisVersion.getLineOfTxt());
						undoStack.pop();
						numberOfUndos--;
					}
					break;
				case ('x'):
					lines.replace(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
					break;
				case ('I'):
					if (undoCmd1 == '~')
						lines.replace(cursorPosition.getY() + 1, restoreThisVersion.getLineOfTxt());
					else
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
			}
			//lines.clear();
			numberOfUndos--;
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
	int cursorXVal;
	int cursorYVal;
	do {
		int doNTimes = 1;
		if (!lines.isEmpty())
		currLine = lines.getEntry(cursorPosition.getY()+1);
		currCommand.clear();
		command = _getwch();
		if (command >= '0' && command <= '9') {
			currCommand += command;
			command = _getwch();
		}
		else {
			currCommand[0] = '1';
		}
			currCommand += command;
		Snapshot cacheSnapshot(cursorPosition, currLine, currCommand );
		if (currCommand[0] >= '0' && currCommand[0] <= '9')
			doNTimes = currCommand[0] - '0';
		while (doNTimes > 0) {
			switch (command)
			{
			case('j'):
				doNTimes--;
				if (!lines.isEmpty()) {
					lengthOfLine = (cursorPosition.getY() + 1) % lines.getLength();
					cursorYVal = cursorPosition.getY();
					if (cursorPosition.getY() < lengthOfLine)
						cursorPosition.setY(cursorYVal + 1);
					break;
			case('l'):
				doNTimes--;
				if (!lines.isEmpty())
					lengthOfLine = lines.getEntry(cursorPosition.getY() + 1).length();
				if (cursorPosition.getX() < lengthOfLine + SPACES_IN_MARGIN - ZERO_INDEX)
					cursorPosition.setX(cursorPosition.getX() + 1);
				break;
			case('k'):
				doNTimes--;
				if (cursorPosition.getY() > 0)
					cursorPosition.setY(cursorPosition.getY() - 1);
				break;
			case('h'):
				doNTimes--;
				if ((cursorPosition.getX() - SPACES_IN_MARGIN) > 0)
					cursorPosition.setX(cursorPosition.getX() - 1);
				break;
			case('d'):
				if (doNTimes > lines.getLength())
					currCommand[0] = lines.getLength() + '0';
				else
					currCommand[0] = '1';
				currLine.clear();
				command = _getwch();
				if (command == 'd') {
					currCommand += command;
					cacheSnapshot.setCommand(currCommand);
					while (doNTimes > 0) {
						//cursorPosition.setY(cursorPosition.getY() + 1);
						cacheSnapshot.setPosition(cursorPosition);
						//cursorPosition.setY(cursorPosition.getY() - 1);
						if (!lines.isEmpty() && doNTimes >= 1)
							undoStack.push(cacheSnapshot);
						
						int numberOfLines = lines.getLength();
						if (numberOfLines > 1) {
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
						doNTimes--;
						if (doNTimes > 0 && !lines.isEmpty()) {
							currLine = lines.getEntry(cursorPosition.getY() + 1);
							cacheSnapshot.setLineOfTxt(currLine);
							cacheSnapshot.setPosition(cursorPosition);
						}
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
				doNTimes--;
				stuffChanged = true;
				break;
			case('u'):
				doNTimes--;
				stuffChanged = undo(undoStack);
				currCommand.clear();
				break;
			case ('I'): {
				doNTimes = 0;
				//reference undoStack in insert to save when changes are made
				Point<int> placeHolder(cursorPosition.getX(), cursorPosition.getY());
				insert();
				//placeCursorAt(placeHolder);
			}
						break;
			default:
				doNTimes--;
				/*Point<int> printOutputHere(0, lines.getLength() + 5);
				placeCursorAt(printOutputHere);
				std::cout << "Would you like to continue editing?\n"
					<< "0 for no, 1 for yes";
				std::cin >> continueEditing;*/
				break;
				}
			}
			//clear screen and print current lines
			if (stuffChanged) {
				system("CLS");
				display(lines);
				stuffChanged = false;
			}
			//done printing lines
			//shift cursor over 
			if (cursorPosition.getX() == 0)
				cursorPosition.setX(SPACES_IN_MARGIN);
			placeCursorAt(cursorPosition);
		}
	} while (command != 'q');

	//finish the editing part of the editor

	//write new line of strings to file


}
