#include "graphm.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#define UNVISITED -1;

using namespace std;

int AdjGraph::n() { return numVertex; }

int AdjGraph::e() { return numEdge; }

AdjGraph::AdjGraph(){}

AdjGraph::AdjGraph(int numVert){ Init(numVert); }

AdjGraph::~AdjGraph(){ delete [] mark; delete [] edges; }

void AdjGraph::Init(int n){
	int i;
	numVertex = n;
	numEdge = 0;
	mark = new int[n]; 
	edges = new int[n];

	for (i=0; i<numVertex; i++)
		mark[i] = UNVISITED;

	for (i = 0; i < numVertex; i++) 
		edges[i] = 0;
}

int AdjGraph::first(int v){ 
	for (int i = 0; i < numVertex; i++)
		if (edges[calculate_edge(v, i)] != 0) return i;
	return numVertex;
};

int AdjGraph::next(int v, int w){ 
	for(int i = w + 1; i < numVertex; i++)
		if (edges[calculate_edge(v, i)] != 0) return i;
	return numVertex;
};

void AdjGraph::setEdge(int v1, int v2, int wght){
	if (edges[calculate_edge(v1, v2)] == 0) numEdge++;
	edges[calculate_edge(v1, v2)] = wght;
};

void AdjGraph::delEdge(int v1, int v2){
	if (edges[calculate_edge(v1, v2)] != 0) numEdge--;
	edges[calculate_edge(v1, v2)] = 0;
}

bool AdjGraph::isEdge(int i, int j){ 
	return edges[calculate_edge(i, j)] != 0; 
}

int AdjGraph::weight(int v1, int v2){ 
	return edges[calculate_edge(v1, v2)]; 
}

int AdjGraph::getMark(int v){ return mark[v]; }

void AdjGraph::setMark(int v, int val){ mark[v] = val; }

int AdjGraph::calculate_edge(int v1, int v2){
	if (v1 > v2) return calculate_edge(v2, v1);
	return ((v1 * (v1 - 1)) / 2) + v2;
}

Graph* read_graph(string filename) {
	/* 
	 * Reads in a csv file in the format of
	 * vertex 1, vertex2, weight. From there
	 * it parses the file by getting each 
	 * required element for the call to setEdge
	 * when it has all the values required, which 
	 * is when count is equal to three, it will 
	 * then push temp to the vector then the 
	 * vector is later used to create the graph
	 */
	ifstream input_file(filename);
	string part;
	vector<GraphInfo> points;
	GraphInfo temp;
	int v1, v2, wt;

	int count = 0;
	while(getline(input_file, part, ',')){
		// Get each arguement for the edge construction
		count++;
		switch(count){
			case 1: v1 = stoi(part); break;
			case 2: v2 = stoi(part); break;
			case 3: wt = stoi(part); break;
		}
		// Push temp onto the vector to save the 
		// point in the graph so it can be added
		if (count % 3 == 0){
			count = 1;
			temp.v1 = v1; 
			temp.v2 = v2; 
			temp.wt = wt;
			points.push_back(temp);
		}
	}

	// Create the graph object from the points in the vector
	AdjGraph *new_graph = new AdjGraph(points.size());
	for(int i = 0; i < points.size(); i++){
		new_graph->setEdge(points[i].v1, points[i].v2, points[i].wt);
	}
	return new_graph;
}  

bool write_graph(Graph *g, string filename) {
	ofstream output_file(filename);


} 

int main(){
	Graph *test = read_graph("input.csv");
	cout << test->isEdge(3, 1) << endl;
	return 0;
}