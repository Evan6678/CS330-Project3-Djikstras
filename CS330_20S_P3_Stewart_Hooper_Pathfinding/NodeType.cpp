#include "NodeType.h"

NodeType::NodeType(int idParam, char symbolParam, int xCordParam, int yCordParam, string nameParam)
{
	id = idParam;
	symbol = symbolParam;
	xCord = xCordParam;
	yCord = yCordParam;
	name = nameParam;
	hasBeenTraversed = false;
	hasBeenExhastedInRequest = false;
}

void NodeType::addConnection(ConnectorType* newConnection)
{
	sourceConnections.push_back(newConnection);
}

void NodeType::addDjikstraConnectors(ConnectorType* newConnection)
{
	djikstraConnections.push_back(newConnection);
}

void NodeType::setHasBeenTraversedFlag(bool flag)
{
	hasBeenTraversed = flag;
}

void NodeType::setHasBeenExhastedInRequest(bool flag)
{
	hasBeenExhastedInRequest = flag;
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

bool NodeType::getHasBeenExhastedInRequest()
{
	return hasBeenExhastedInRequest;
}

string NodeType::getName()
{
	return name;
}

list<ConnectorType*> NodeType::getSourceConnectionList()
{
	return sourceConnections;
}

list<ConnectorType*> NodeType::getDjikstraConnectors()
{
	return djikstraConnections;
}
