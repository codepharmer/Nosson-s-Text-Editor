#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Point.h"

class Snapshot{
	public:
		Snapshot();
		Snapshot(Point<int>, std::string );
		std::string getCachedLineOfTxt()const;
		Point<int> getCachedPosition()const;

	private:
		std::string cachedLineOfTxt;
		Point<int> cachedPosition;
};
