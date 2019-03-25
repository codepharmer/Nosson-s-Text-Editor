#include "Xeditor.h"
#include <iostream>
#include <string>
#include <cstring>

int main()
{
	Xeditor myEditor;
	myEditor.readfile("forXeditor.txt");

	myEditor.run();
	system("PAUSE");
	return 0;
}