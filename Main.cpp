#include "Xeditor.h"
#include <iostream>
#include <string>
#include <cstring>

int main()
{
	Xeditor myEditor;
	myEditor.readfile("forXeditor.txt");

	myEditor.run();
	//maybe write a method to clear screen before exiting
	//myEditor.exit();
	system("PAUSE");
	return 0;
}