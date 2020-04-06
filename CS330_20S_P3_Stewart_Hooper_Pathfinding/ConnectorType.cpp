#include "ConnectorType.h"

ConnectorType::ConnectorType(int idParam, char symbolParam, NodeType* sourceNodeIdParam, NodeType* destinationNodeIdParam, int costParam)
{
	id = idParam;
	symbol = symbolParam;
	sourceNode = sourceNodeIdParam;
	destinationNode = destinationNodeIdParam;
	cost = costParam;
}

int ConnectorType::getId()
{
	return id;
}

char ConnectorType::getSymbol()
{
	return symbol;
}

NodeType* ConnectorType::getsourceNode()
{
	return sourceNode;
}

NodeType* ConnectorType::getdestinationNode()
{
	return destinationNode;
}

int ConnectorType::getCost()
{
	return cost;
}
