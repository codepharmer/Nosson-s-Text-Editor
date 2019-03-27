#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Point.h"

class Snapshot{
	public:
		Snapshot();
		Snapshot(Point<int>, std::string, std::string );
		std::string getLineOfTxt()const;
		std::string getCommand()const;
		Point<int> getPosition()const;
		void setLineOfTxt(const std::string );
		void setCommand(const std::string);
		void setPosition(const Point<int>);

	private:
		std::string cachedLineOfTxt;
		Point<int> cachedPosition;
		std::string cachedCommand;
};
