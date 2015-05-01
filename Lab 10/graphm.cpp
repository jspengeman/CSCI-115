#include "graphm.h"

// AdjGraph::AdjGraph(){}

AdjGraph::~AdjGraph(){}

void AdjGraph::Init(int n){}

int AdjGraph::e(){ return 0; }

int AdjGraph::n(){ return 0; }

int AdjGraph::first(int v){ return 0; };

int AdjGraph::next(int v, int w){ return 0; };

void AdjGraph::setEdge(int v1, int v2, int wght){};

void AdjGraph::delEdge(int v1, int v2){}

bool AdjGraph::isEdge(int i, int j){ return false; }

int AdjGraph::weight(int v1, int v2){ return 0; }

int AdjGraph::getMark(int v){ return 0; }

void AdjGraph::setMark(int v, int val){}

Graph* AdjGraph::read_graph(string filename) { return NULL; }  

bool AdjGraph::write_graph(Graph *g, string filename) { return false; } 

int main(){
	return 0;
}