#include "Snapshot.h"

Snapshot::Snapshot()
{
}

Snapshot::Snapshot( Point<int> inPosition, std::string inCachedTxt)
{
	cachedLineOfTxt = inCachedTxt;
	cachedPosition = inPosition;
}

std::string Snapshot::getCachedLineOfTxt() const
{
	return cachedLineOfTxt;
}

Point<int> Snapshot::getCachedPosition() const
{
	return cachedPosition;
}
