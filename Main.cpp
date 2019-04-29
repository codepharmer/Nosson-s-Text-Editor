#include "Xeditor.h"
#include <iostream>
#include <string>
#include <cstring>

int main( int argc, char * argv[])
{
	Xeditor myEditor;
	myEditor.readfile("forXeditor.txt");

	myEditor.run();
	//maybe write a method to clear screen before exiting
	//myEditor.exit();
	cin.get();
	return 0;
}