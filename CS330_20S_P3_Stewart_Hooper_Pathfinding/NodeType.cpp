#include "NodeType.h"

NodeType::NodeType(int idParam, char symbolParam, int xCordParam, int yCordParam, string nameParam)
{
	id = idParam;
	symbol = symbolParam;
	xCord = xCordParam;
	yCord = yCordParam;
	name = nameParam;
	hasBeenTraversed = false;
}

void NodeType::addConnection(ConnectorType* newConnection)
{
	sourceConnections.push_back(newConnection);
}

void NodeType::setHasBeenTraversedFlag(bool flag)
{
	hasBeenTraversed = flag;
}

int NodeType::getId()
{
	return id;
}

char NodeType::getSymbol()
{
	return symbol;
}

int NodeType::getXCord()
{
	return xCord;
}

int NodeType::getYCord()
{
	return yCord;
}

bool NodeType::getHasBeenTraversed()
{
	return hasBeenTraversed;
}

string NodeType::getName()
{
	return name;
}

list<ConnectorType*> NodeType::getSourceConnectionList()
{
	return sourceConnections;
}
