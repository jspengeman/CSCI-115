#include <iostream> 
#include "graphm.h"
#include "ParPtrTree.h"
#include "heap.cpp"
#define REGISTERS 10

using namespace std;

Graph *graph[REGISTERS];
ParPtrTree *comps[REGISTERS];
int numcomps[REGISTERS];

// An element for the heap
class KruskElem { 
public:
	// The edge being stored
	int from, to, distance; 
	KruskElem() { from = -1; to = -1; distance = -1; }
	KruskElem(int f, int t, int d){ from = f; to = t; distance = d; }
};

inline bool operator>(const KruskElem& lhs, const KruskElem& rhs){
	return rhs.distance < lhs.distance;
}

inline bool operator<(const KruskElem& lhs, const KruskElem& rhs){
	return rhs.distance > lhs.distance;
}


// Kruskal’s MST algorithm
void Kruskel(Graph* G, Graph* m) { 
	// Equivalence class array
	ParPtrTree *A = new ParPtrTree(G->n());
	// Array of edges for min-heap
	KruskElem *E = new KruskElem[G->e()];

	int i;
	int edgecnt = 0;
	// Put the edges on the array
	for (i = 0; i < G->n(); i++) {
		// Modified for undirected graph
		for (int w = G->next(i, i); w < G->n(); w = G->next(i,w)) {
			E[edgecnt].distance = G->weight(i, w);
			E[edgecnt].from = i;
			E[edgecnt++].to = w;
		}
	}

	// Heapify the edges
	heap<KruskElem, Min> H(E, edgecnt, edgecnt);
	// Initially n equiv classes
	int numMST = G->n(); 
	// Combine equiv classes
	for (i = 0; numMST > 1; i++) { 
		KruskElem temp;
		// Get next cheapest edge
		temp = H.removefirst(); 
		int v = temp.from; int u = temp.to;
		// If in different equiv classes
		if (A->differ(v, u)) {
			// Combine equiv classes 
			A->UNION(v, u); 
			// Add edge to MST
			m->setEdge(temp.from, temp.to, temp.distance); 
			numMST--; 
		}
	}
	delete A;
	delete []E;
}

int main(){
	Graph *g = new GraphM(6);
	// Example from openDSA
  	g->setEdge(0,2,7);
    g->setEdge(0,4,9);
    g->setEdge(1,2,5);
    g->setEdge(1,5,6);
    g->setEdge(2,3,1);
    g->setEdge(2,4,3);
    g->setEdge(3,5,2);
    g->setEdge(4,5,1);
    Graph *m = new GraphM(6);

    graph[0] = m;

    Kruskel(g, graph[0]);
    graph[0]->viewGraph();

    Graph *t = new GraphM(4);
    t->setEdge(0, 1, 5);
    t->setEdge(1, 2, 3);
    t->setEdge(2, 3, 2);
    t->setEdge(3, 4, 7);
    Graph *f = new GraphM(4);

    Kruskel(t, f);
    f->viewGraph();

    delete t;
    delete f;
    delete g;
    delete m;
	return 0;
}