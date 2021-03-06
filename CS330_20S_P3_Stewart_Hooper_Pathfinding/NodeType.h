#pragma once
#include <string>
#include <list>

class ConnectorType;								//Forward declaration to prevernt circular dependency issues

using namespace std;

class NodeType
{

private: 
	int id;												//id number for node, is based sequentially on when node data was read in
	char symbol;										//Symbol for node "N"
	int xCord;											//X Coordinate data
	int yCord;											//Y Coordinate data
	bool hasBeenTraversed;								//will be true when the node is is accessed while finding shortest path
	bool hasBeenExhastedInRequest;						//Will be true when all djikstra paths have been used and failed in a search
	string name;										//String defined name
	list<ConnectorType*>sourceConnections;				//list of connections where this node is the source
	list<ConnectorType*>djikstraConnections;			//list of connections where this node is the source

public:
	NodeType(int idParam, char symbolParam, int xCordParam, int yCordParam, string nameParam);			//constructor to load the data

	void addConnection(ConnectorType* newConnection);													//add a new connection
	void addDjikstraConnectors(ConnectorType* newConnection);											//add new djikstra connection
	void setHasBeenTraversedFlag(bool flag);
	void setHasBeenExhastedInRequest(bool flag);									

	int getId();																						//get the id of node
	char getSymbol();																					//get the symbol of node
	int getXCord();																						//get the x coordinate of node
	int getYCord();																						//get the y coordinate of node
	bool getHasBeenTraversed();																			//get the boolean for if the node has been accessed
	bool getHasBeenExhastedInRequest();
	string getName();																					//get the name of node
	list<ConnectorType*> getSourceConnectionList();														//get the list of source connections
	list<ConnectorType*> getDjikstraConnectors();														//get the list of shortest path connections
};

