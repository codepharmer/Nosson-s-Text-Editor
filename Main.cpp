#include "Xeditor.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main( int argc, char * argv[])
{
	//for (int i = 0; i < argc; i++)
		//cout << i << " " << argv[i] << endl;
	string userFile;
	userFile = argv[1];
	//cout << "Enter a filename.\n";
	//cin >> userFile;
	Xeditor myEditor;
	myEditor.readfile(userFile);
	myEditor.run();
	//maybe write a method to clear screen before exiting
	//myEditor.exit();
	cin.get();
	return 0;
}