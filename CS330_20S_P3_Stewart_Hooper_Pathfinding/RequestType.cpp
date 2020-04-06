#include "RequestType.h"

RequestType::RequestType(int idParam, char symbolParam, NodeType* sourceParam, NodeType* endParam)
{
	id = idParam;
	symbol = symbolParam;
	sourceNode = sourceParam;
	endNode = endParam;
}

void RequestType::addRequstPathNode(NodeType* newNode)
{
	requestPath.push_back(newNode);
}

int RequestType::getId()
{
	return id;
}

char RequestType::getSymbol()
{
	return symbol;
}

NodeType* RequestType::getSourceNode()
{
	return sourceNode;
}

NodeType* RequestType::getEndNode()
{
	return endNode;
}

list<NodeType*> RequestType::getRequestPath()
{
	return requestPath;
}
