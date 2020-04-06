#pragma once

#include <list>

using namespace std;

class NodeType;

class RequestType
{
private:
	int id;								//request id
	char symbol;						//request symbol "R"
	NodeType* sourceNode;				//the starting node for the traversal
	NodeType* endNode;					//the ending node for the traversal
	list<NodeType*>requestPath;			//The path from src -> dest node

public:
	RequestType(int idParam, char symbolParam, NodeType* sourceParam, NodeType* endParam);		//constructor to load a new request

	void addRequstPathNode(NodeType* newNode);													//adds a new node to the request path list

	int getId();																				//get the id
	char getSymbol();																			//get the symbol
	NodeType* getSourceNode();																	//get the source node
	NodeType* getEndNode();																		//get the end node
	list<NodeType*>getRequestPath();															//gets the list of nodes to traverse path
};

