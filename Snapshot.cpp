#include "Snapshot.h"

Snapshot::Snapshot()
{
}

Snapshot::Snapshot( Point<int> inPosition, std::string inCachedTxt, std::string inCachedCommand)
{
	cachedLineOfTxt = inCachedTxt;
	cachedPosition = inPosition;
	cachedCommand = inCachedCommand;
}

std::string Snapshot::getLineOfTxt() const
{
	return cachedLineOfTxt;
}

std::string Snapshot::getCommand() const
{
	return cachedCommand;
}

Point<int> Snapshot::getPosition() const
{
	return cachedPosition;
}

void Snapshot::setLineOfTxt(const std::string inLineOfTxt)
{
	cachedLineOfTxt = inLineOfTxt;
}

void Snapshot::setCommand(const std::string inCommand)
{
	cachedCommand = inCommand;
}

void Snapshot::setPosition(const Point<int> inPosition)
{
	cachedPosition = inPosition;
}