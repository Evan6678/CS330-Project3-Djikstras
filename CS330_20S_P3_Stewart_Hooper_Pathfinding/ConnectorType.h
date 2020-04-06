#pragma once

class NodeType;											//Forward declaration to prevernt circular dependency issues

using namespace std;
class ConnectorType
{

private:
	int id;												//id number for Connector, is based sequentially on when connector data was read in
	char symbol;										//Symbol for Connector "C"
	NodeType* sourceNode;								//The source node we are traversing from 
	NodeType* destinationNode;							//The destination node we are traversing to
	int cost;											//cost to traverse this connection

public:
	ConnectorType(int idParam, char symbolParam, NodeType* sourceNodeIdParam, NodeType* destinationNodeIdParam, int costParma);			//constructor to load the data

	int getId();																						//get the id of connector
	char getSymbol();																					//get the symbol of connector
	NodeType* getsourceNode();																			//get the x coordinate of connector
	NodeType* getdestinationNode();																		//get the y coordinate of connector
	int getCost();																						//return node cost

};

