#pragma once

#include <list>

#include "NodeType.h"
#include "ConnectorType.h"
#include "RequestType.h"

using namespace std;

class NodeTreeSingleton
{
private:
	static NodeTreeSingleton* instance;																											//instance of the singleton
	list<NodeType*> nodeList;																													//List of all nodes 
	list<ConnectorType*> connectorList;																											//List of all connectors
	list<ConnectorType*> djikstraConnectorList;																									//List of the refined connectors to map the shortest path
	list<RequestType*> requestList;																												//List of all requests

	list<ConnectorType*> possibleConnectorList;																									//As we perform shortest path algorithm we keep track of the list of possible paths we can take

	NodeTreeSingleton();																														//singleton constructor, inits data to empty state

	NodeType* getNodeFromSingletonNodeListById(int idParam);																					//get a node from the list by id number, if no node exists return null
	ConnectorType* getConnectorFromSingletonListById(int idParam);																				//get a connection from the list by it, if no connection exists return null
	RequestType* getRequestFromSingletonListById(int idParam);																					//get a request from the list by id
	list<ConnectorType*> getAllConnectorsFromNodeById(int idParam);																				//get a list of all the connections from a given node by Id
	bool addConnectorToSourceNode(int nodeId, ConnectorType* connector);																		//Add a connector reference to the array in the source node
	bool addDjikstraConnectorToSourceNode(int nodeId, ConnectorType* connector);																//add the shortest path options to source nodes while performing Dijkstra alg

public:
	static NodeTreeSingleton* getInstance();		//get the instance of the singleton if exists
	static NodeTreeSingleton* getNewInstance();		//gets a new instance and throws out all old data

	bool addNodeToSingletonNodeList(int idParam, char symbolParam, int xCordParam, int yCordParam, string nameParam);							//method to add new node into the list, will return true if successful
	bool addconnectorToSingletonNodeList(int idParam, char symbolParam, int sourceNodeIdParam, int destinationNodeIdParam, int costParma);		//method to add new connection into the list, will return true if successful
	bool addRequestToSingletonRequestList(int idParam, char symbolParam, int sourceNodeIdParam, int destinationNodeIdParam);					//method to add new request into the list
	bool addConnectorToSingletonDjikstraConnectorListById(int connectorId);																		//Once we find a connector for shortest path add it to new list
	bool addConnectorsToSingletonPossibleConnectorListByNodeId(int idParam);																	//Add connectors that we can pick from in this list

	bool removeConnectorToSingletonPossibleConnectorListById(int connectorId);																	//once we add a connector to the djikstra list we need to remove as option in possible list

	void setNodeHasBeenTraversedFlagById(int idParam, bool flag);																				//sets the nodes has been traversed flag

	int getConnectorDestinationNodeIdByConnectorId(int connectorId);																			//return the destination node id from the connection between 2 nodes

	int getShortestPathFromSingletonPossibleConnectorsList();																					//loop through and find the shortest path in the possible connectors list to return id of connector
																										
	int getNodeListLength();																													//get the length of the respective list
	int getConnectorListLength();																												//get the length of the respective list
	int getDjikstraConnectorListLength();																										//get the length of the respective list
	int getRequestListLength();																													//get the length of the respective list
	int getPossibleConnectorListLength();																										//get the length of the respective list

	char getNodeSymbolById(int idParam);
	int getNodeXCordById(int idParam);
	int getNodeYCordById(int idParam);
	string getNodeNameById(int idParam);

	char getConnectorSymbolById(int idParam);
	int getConnectorSourceNodeIdById(int idParam);
	int getConnectorCostById(int idParam);

	char getRequestSymbolById(int idParam);
	int getRequestSourceNodeIdById(int idParam);
	int getRequestDestinationNodeIdById(int idParam);

	bool hasAllNodesBeenMapped();																												//checks all the nodes if they have been mapped, returns true if they have all been accessed

};

