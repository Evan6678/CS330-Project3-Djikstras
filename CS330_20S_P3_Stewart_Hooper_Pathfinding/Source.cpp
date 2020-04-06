#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

#include "NodeTreeSingleton.h"

using namespace std;

void readAndLoadData(string , NodeTreeSingleton*);
void dijkstaShortestPath(NodeTreeSingleton*);
void outputData(NodeTreeSingleton*);

int main() {

	//get users input file
	string userInputFile = "CS 330 20S, Graph Adventure Bay v3.txt";

	//get instance of singleton 
	NodeTreeSingleton* nodeCollectionSingleton = nodeCollectionSingleton->getInstance();

	//read in the data from the input file into the 
	readAndLoadData(userInputFile, nodeCollectionSingleton);

	//use dijsktra to traverse nodes and get shortest paths
	dijkstaShortestPath(nodeCollectionSingleton);

	//output data to output file
	outputData(nodeCollectionSingleton);

	return 0;
}

void readAndLoadData(string fileName, NodeTreeSingleton* nodeCollectionSingleton) {
	fstream inputFile;
	inputFile.open(fileName, ios::in);
	
	//if file opens continue
	if (inputFile.is_open()) {
		string linePointer;

		int nodeIdCounter = 1;
		int connectionIdCounter = 1;
		int requestIdCounter = 1;

		//while we continue to read new lines in
		while (getline(inputFile, linePointer)) {
			
			//tokenize the string
			istringstream buffer(linePointer);
			istream_iterator<string> beg(buffer), end;
			vector<string> tokens(beg, end);
			
			//load the data
			if (tokens.front() == "N") {
				string nameField = "";

				if (tokens.size() == 4) {
					nameField = tokens.at(3);
				}

				nodeCollectionSingleton->addNodeToSingletonNodeList(nodeIdCounter, 'N', stoi(tokens.at(1)) , stoi(tokens.at(2)), nameField);
				nodeIdCounter++;
			}
			else if (tokens.front() == "C") {

				nodeCollectionSingleton->addconnectorToSingletonNodeList(connectionIdCounter, 'C', stoi(tokens.at(1)), stoi(tokens.at(2)), stoi(tokens.at(3)));
				connectionIdCounter++;
			}
			else if (tokens.front() == "R") {
				nodeCollectionSingleton->addRequestToSingletonRequestList(requestIdCounter, 'R', stoi(tokens.at(1)), stoi(tokens.at(2)));
				requestIdCounter++;
			}
		}
	}
	else {
		cout << "\nError openining file\n";
		exit(1);
	}
}

void dijkstaShortestPath(NodeTreeSingleton* nodeCollectionSingleton) {
	int currentNodeId = 1;
	int currentConnectorId = 0;
	
	//while we still have a node that is not mapped we continue to map shortest path algorithm 
	while (!nodeCollectionSingleton->hasAllNodesBeenMapped()) {

		//set the flag on current node that we have mapped it
		nodeCollectionSingleton->setNodeHasBeenTraversedFlagById(currentNodeId, true);

		//extra check to catch case where last node is creating a null pointer excpetion
		if (nodeCollectionSingleton->hasAllNodesBeenMapped()) break;

		//get the list of all connections from this node and store in list of possible connections
		nodeCollectionSingleton->addConnectorsToSingletonPossibleConnectorListByNodeId(currentNodeId);

		//get the shortest path from all the possible connectors
		currentConnectorId = nodeCollectionSingleton->getShortestPathFromSingletonPossibleConnectorsList();

		//store the new shortest path connection into the djikstras list of connectors
		nodeCollectionSingleton->addConnectorToSingletonDjikstraConnectorListById(currentConnectorId);

		//remove the current connector that we added to djikstras list from the possible connectors list
		nodeCollectionSingleton->removeConnectorToSingletonPossibleConnectorListById(currentConnectorId);

		//get the destination node from this new connection and set as current node id
		currentNodeId = nodeCollectionSingleton->getConnectorDestinationNodeIdByConnectorId(currentConnectorId);
	}
}

void outputData(NodeTreeSingleton* nodeCollectionSingleton) {
	ofstream outfile;

	outfile.open("CS330_20S_P3_Stewart_Hopper_Results.txt", ios::out);

	if (outfile.is_open()) {
		//Header
		outfile << "=====================================================";
		outfile << endl << "CS330 Project 3 output file" << endl;
		outfile << "=====================================================";
		outfile << endl << "=====================================================";

		//raw data output
		outfile << endl << endl << "==>Raw input data for result run" << endl;
		outfile << endl << "Number of input nodes: " << nodeCollectionSingleton->getNodeListLength() << endl;
		outfile << "Number of input connections: " << nodeCollectionSingleton->getConnectorListLength() << endl;
		outfile << "Number of input requests: " << nodeCollectionSingleton->getRequestListLength() << endl;

		//print nodes
		outfile << "=====================================================";
		outfile << endl << "=>Node List" << endl << endl;

		for (int x = 1; x < nodeCollectionSingleton->getNodeListLength(); x++) {
			outfile << nodeCollectionSingleton->getNodeSymbolById(x) << " " << nodeCollectionSingleton->getNodeXCordById(x) << " " << nodeCollectionSingleton->getNodeYCordById(x) << " " << nodeCollectionSingleton->getNodeNameById(x) << endl;
		}

		//print connectors
		outfile << "=====================================================";
		outfile << endl << "=>Connector List" << endl << endl;

		for (int x = 1; x < nodeCollectionSingleton->getConnectorListLength(); x++) {
			outfile << nodeCollectionSingleton->getConnectorSymbolById(x) << " " << nodeCollectionSingleton->getConnectorSourceNodeIdById(x) << " " << nodeCollectionSingleton->getConnectorDestinationNodeIdByConnectorId(x) << " " << nodeCollectionSingleton->getConnectorCostById(x) << endl;
		}

		//print requests
		outfile << "=====================================================";
		outfile << endl << "=>Request List" << endl << endl;

		for (int x = 1; x < nodeCollectionSingleton->getRequestListLength(); x++) {
			outfile << nodeCollectionSingleton->getRequestSymbolById(x) << " " << nodeCollectionSingleton->getRequestSourceNodeIdById(x) << " " << nodeCollectionSingleton->getRequestDestinationNodeIdById(x) << endl;
		}

		//print Djikstras map data
		outfile << endl << endl << "=====================================================";
		outfile << endl << "=====================================================";
		outfile << endl << endl << "==>All Djikstras mapped connectors for shortest path to all nodes" << endl;

		//print connectors
		outfile << "=====================================================";
		outfile << endl << "=>Connector List" << endl << endl;

		for (int x = 1; x < nodeCollectionSingleton->getDjikstraConnectorListLength(); x++) {
			outfile << nodeCollectionSingleton->getConnectorSymbolById(x) << " " << nodeCollectionSingleton->getConnectorSourceNodeIdById(x) << " " << nodeCollectionSingleton->getConnectorDestinationNodeIdByConnectorId(x) << " " << nodeCollectionSingleton->getConnectorCostById(x) << endl;
		}
	}
}