#include <iostream>
#include "graphm.h"
#include "ParPtrTree.h"
#include "heap.cpp"

using namespace std;

int main(){
	Graph *graph = read_graph("input.csv");
	cout << "Graph tests" << endl;
	cout << graph->isEdge(1, 2) << endl;
	cout << graph->isEdge(2, 3) << endl;
	cout << graph->isEdge(1, 3) << endl;
	cout << graph->isEdge(2, 4) << endl;
	cout << graph->isEdge(3, 4) << endl;

	cout << graph->weight(1, 2) << endl;
	cout << graph->weight(2, 3) << endl;
	cout << graph->weight(1, 3) << endl;
	cout << graph->weight(2, 4) << endl;
	cout << graph->weight(3, 4) << endl;

	graph->setEdge(5, 1, 30);
	cout << graph->isEdge(1, 5) << endl;
	graph->delEdge(5, 1);
	cout << graph->isEdge(1, 5) << endl;
	graph->setEdge(6, 3, 45);
	cout << graph->isEdge(6, 3) << endl;
	graph->delEdge(6, 3);
	cout << graph->isEdge(6, 3) << endl;

	return 0;
}