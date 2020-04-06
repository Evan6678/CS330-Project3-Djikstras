#include "NodeTreeSingleton.h"

NodeTreeSingleton* NodeTreeSingleton::instance = 0;		//define instance of singleton

NodeTreeSingleton::NodeTreeSingleton()
{
	nodeList = { };
	connectorList = { };
	requestList = { };
	djikstraConnectorList = { };
	possibleConnectorList = { };
}

NodeTreeSingleton* NodeTreeSingleton::getInstance()
{
	if (!instance) {
		instance = new NodeTreeSingleton;
		return instance;
	}
}

NodeTreeSingleton* NodeTreeSingleton::getNewInstance()
{
	instance = new NodeTreeSingleton;
	return instance;
}

bool NodeTreeSingleton::addNodeToSingletonNodeList(int idParam, char symbolParam, int xCordParam, int yCordParam, string nameParam)
{
	try {
		NodeType* newNode = new NodeType(idParam, symbolParam, xCordParam, yCordParam, nameParam);
		nodeList.push_back(newNode);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NodeTreeSingleton::addconnectorToSingletonNodeList(int idParam, char symbolParam, int sourceNodeIdParam, int destinationNodeIdParam, int costParma)
{
	try {
		ConnectorType* newConnector = new ConnectorType(idParam, symbolParam, getNodeFromSingletonNodeListById(sourceNodeIdParam), getNodeFromSingletonNodeListById(destinationNodeIdParam), costParma);
		addConnectorToSourceNode(sourceNodeIdParam, newConnector);
		connectorList.push_back(newConnector);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NodeTreeSingleton::addRequestToSingletonRequestList(int idParam, char symbolParam, int sourceNodeIdParam, int destinationNodeIdParam)
{
	try {
		RequestType* newRequest = new RequestType(idParam, symbolParam, getNodeFromSingletonNodeListById(sourceNodeIdParam), getNodeFromSingletonNodeListById(destinationNodeIdParam));
		requestList.push_back(newRequest);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NodeTreeSingleton::addConnectorToSourceNode(int nodeId, ConnectorType* connector)
{
	try {
		NodeType* sourceNode = getNodeFromSingletonNodeListById(nodeId);
		sourceNode->addConnection(connector);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NodeTreeSingleton::addDjikstraConnectorToSourceNode(int nodeId, ConnectorType* connector)
{
	try {
		NodeType* sourceNode = getNodeFromSingletonNodeListById(nodeId);
		sourceNode->addDjikstraConnectors(connector);
	}
	catch (...) {
		return false;
	}
	return true;
}

void NodeTreeSingleton::resetAllNodesExhaustedFlag()
{
	for (list<NodeType*>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		(*it)->setHasBeenExhastedInRequest(false);
	}
}

bool NodeTreeSingleton::addConnectorToSingletonDjikstraConnectorListById(int connectorId)
{
	try {
		ConnectorType* connector = getConnectorFromSingletonListById(connectorId);
		addDjikstraConnectorToSourceNode(connector->getsourceNode()->getId(), connector);

		djikstraConnectorList.push_back(connector);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NodeTreeSingleton::addConnectorsToSingletonPossibleConnectorListByNodeId(int idParam)
{

	list<ConnectorType*> connectors = getAllConnectorsFromNodeById(idParam);

	try {
		//search through the new connectors list, if the destination node has already been traversed then do not add to list of new traversable connections

		list<ConnectorType*> connectorsToRemove;

		for (list<ConnectorType*>::iterator it = connectors.begin(); it != connectors.end(); it++) {
			NodeType* destinationNode = (*it)->getdestinationNode();
			
			if (destinationNode->getHasBeenTraversed() == true) {
				connectorsToRemove.push_back(*it);
			}
		}

		for (list<ConnectorType*>::iterator it = connectorsToRemove.begin(); it != connectorsToRemove.end(); it++) {
			connectors.remove(*it);
		}

		possibleConnectorList.insert(possibleConnectorList.end(), connectors.begin(), connectors.end());
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NodeTreeSingleton::removeConnectorToSingletonPossibleConnectorListById(int connectorId)
{
	try {
		ConnectorType* connector = getConnectorFromSingletonListById(connectorId);
		possibleConnectorList.remove(connector);
	}
	catch (...) {
		return false;
	}
	return true;
}

void NodeTreeSingleton::setNodeHasBeenTraversedFlagById(int idParam, bool flag)
{
	NodeType* node = getNodeFromSingletonNodeListById(idParam);
	node->setHasBeenTraversedFlag(flag);
}

int NodeTreeSingleton::getConnectorDestinationNodeIdByConnectorId(int connectorId)
{
	ConnectorType* connector = getConnectorFromSingletonListById(connectorId);
	return connector->getdestinationNode()->getId();
}

NodeType* NodeTreeSingleton::getNodeFromSingletonNodeListById(int idParam)
{
	for (list<NodeType*>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		if ((*it)->getId() == idParam) {
			return *it;
		}
	}
	return NULL;
}

ConnectorType* NodeTreeSingleton::getConnectorFromSingletonListById(int idParam)
{
	for (list<ConnectorType*>::iterator it = connectorList.begin(); it != connectorList.end(); it++) {
		if ((*it)->getId() == idParam) {
			return *it;
		}
	}
	return NULL;
}

RequestType* NodeTreeSingleton::getRequestFromSingletonListById(int idParam)
{
	for (list<RequestType*>::iterator it = requestList.begin(); it != requestList.end(); it++) {
		if ((*it)->getId() == idParam) {
			return *it;
		}
	}
	return NULL;
}

int NodeTreeSingleton::getShortestPathFromSingletonPossibleConnectorsList()
{
	int cost = 99999;
	ConnectorType* returnConnector = NULL;

	for (list<ConnectorType*>::iterator it = possibleConnectorList.begin(); it != possibleConnectorList.end(); it++) {
		if ((*it)->getCost() < cost) {
			cost = (*it)->getCost();
			returnConnector = (*it);
		}
	}
	return returnConnector->getId();
}

list<NodeType*> NodeTreeSingleton::getShortestPathBetweenTwoNodesById(int nodeOne, int nodeTwo)
{
	NodeType* currentNode = getNodeFromSingletonNodeListById(nodeOne);
	ConnectorType* currentConnector = NULL;
	NodeType* endNode = getNodeFromSingletonNodeListById(nodeTwo);

	list<NodeType*> requestShortestPath;

	//while we havnet found the end node keep traversing
	while (currentNode != endNode) {
		
		//if the node we are on has no djikstra connectors on the list then it is an end node, backtrack up the tree to continue traversing
		if (currentNode->getDjikstraConnectors().size() == 0) {
			currentNode->setHasBeenExhastedInRequest(true);
			requestShortestPath.remove(currentNode);
			currentNode = requestShortestPath.back();
		}
		else {
			//find the smallest cost connector to current node that has not been exhausted to traverse next
			int cost = 99999;

			list<ConnectorType*> node1PathsList = currentNode->getDjikstraConnectors();

			for (list<ConnectorType*>::iterator it = node1PathsList.begin(); it != node1PathsList.end(); it++) {
				if ((*it)->getCost() < cost && !(*it)->getdestinationNode()->getHasBeenExhastedInRequest()) {
					cost = (*it)->getCost();
					currentConnector = (*it);
				}
			}

			//if the for loop did not find a connector that has not been exhausted then cost = 99999 so we know this node has been exhausted
			if (cost == 99999) {
				currentNode->setHasBeenExhastedInRequest(true);
				requestShortestPath.remove(currentNode);
				currentNode = requestShortestPath.back();
			}
			//else we know the current node has not been fully traversed so dig down into its children nodes
			else {

				//add the current node onto the list stack if it doenst exist already
				if (requestShortestPath.size() == 0 || requestShortestPath.back() != currentNode) {
					requestShortestPath.push_back(currentNode);
				}

				//make the current node the next node in the connection
				currentNode = currentConnector->getdestinationNode();
			}
		}
	}

	//once current node == end node push onto stack and return 
	requestShortestPath.push_back(currentNode);
	resetAllNodesExhaustedFlag();
	return requestShortestPath;
}

list<ConnectorType*> NodeTreeSingleton::getAllConnectorsFromNodeById(int idParam)
{
	NodeType* node = getNodeFromSingletonNodeListById(idParam);
	return node->getSourceConnectionList();
}

int NodeTreeSingleton::getNodeListLength()
{
	return nodeList.size();
}

int NodeTreeSingleton::getConnectorListLength()
{
	return connectorList.size();
}

int NodeTreeSingleton::getDjikstraConnectorListLength()
{
	return djikstraConnectorList.size();
}

int NodeTreeSingleton::getRequestListLength()
{
	return requestList.size();
}

int NodeTreeSingleton::getPossibleConnectorListLength()
{
	return possibleConnectorList.size();
}

char NodeTreeSingleton::getNodeSymbolById(int idParam)
{
	NodeType* node = getNodeFromSingletonNodeListById(idParam);
	return node->getSymbol();
}

int NodeTreeSingleton::getNodeXCordById(int idParam)
{
	NodeType* node = getNodeFromSingletonNodeListById(idParam);
	return node->getXCord();
}

int NodeTreeSingleton::getNodeYCordById(int idParam)
{
	NodeType* node = getNodeFromSingletonNodeListById(idParam);
	return node->getYCord();
}

string NodeTreeSingleton::getNodeNameById(int idParam)
{
	NodeType* node = getNodeFromSingletonNodeListById(idParam);
	return node->getName();
}

char NodeTreeSingleton::getConnectorSymbolById(int idParam)
{
	ConnectorType* connector = getConnectorFromSingletonListById(idParam);
	return connector->getSymbol();
}

int NodeTreeSingleton::getConnectorSourceNodeIdById(int idParam)
{
	ConnectorType* connector = getConnectorFromSingletonListById(idParam);
	return connector->getsourceNode()->getId();
}

int NodeTreeSingleton::getConnectorCostById(int idParam)
{
	ConnectorType* connector = getConnectorFromSingletonListById(idParam);
	return connector->getCost();
}

char NodeTreeSingleton::getRequestSymbolById(int idParam)
{
	RequestType* request = getRequestFromSingletonListById(idParam);
	return request->getSymbol();
}

int NodeTreeSingleton::getRequestSourceNodeIdById(int idParam)
{
	RequestType* request = getRequestFromSingletonListById(idParam);
	return request->getSourceNode()->getId();
}

int NodeTreeSingleton::getRequestDestinationNodeIdById(int idParam)
{
	RequestType* request = getRequestFromSingletonListById(idParam);
	return request->getEndNode()->getId();
}

bool NodeTreeSingleton::hasAllNodesBeenMapped()
{
	for (list<NodeType*>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		if ((*it)->getHasBeenTraversed() == false) {
			return false;
		}
	}

	return true;
}

void NodeTreeSingleton::clearDjikstraConnectorList()
{
	djikstraConnectorList.empty();
}
