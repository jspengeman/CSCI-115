#include "graphm.h"
#define UNVISITED -1;

#include <iostream>
using namespace std;

int AdjGraph::n() { return numVertex; }

int AdjGraph::e() { return numEdge; }

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

Graph* AdjGraph::read_graph(string filename) { return NULL; }  

bool AdjGraph::write_graph(Graph *g, string filename) { return false; } 

int AdjGraph::calculate_edge(int vertex1, int vertex2){
	return ((vertex1 * (vertex1 - 1)) / 2) + vertex2;
}

int main(){
	AdjGraph *test = new AdjGraph(5);
	test->setEdge(1, 2, 50);
	test->setEdge(1, 3, 100);
	test->setEdge(2, 4, 70);
	cout << test->weight(2, 4) << endl;
	cout << test->next(2, 2) << endl;
	return 0;
}