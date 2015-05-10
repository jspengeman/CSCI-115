#include <iostream> 
#include <string>
#include <algorithm>
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
void Kruskal(Graph* G, Graph* m) { 
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

int components(Graph* g, ParPtrTree* t) {
    t = new ParPtrTree(g->n());
    int numofComps = g->n();
    for (int i = 0; i < g->n(); ++i) {
        for (int w = g->next(i, i); 
        	 w < g->n(); w = g->next(i, w)) {
            if (t->differ(i, w)) {
                t->UNION(i, w);
                numofComps--;
            }
        }
    }
    return numofComps;
}

// This function assumes the user
// enters the input string in the
// exact format that was specified
// in the lab write up
void inputCmd(string command){
	// Remove input from the command string
	int start_pos = command.find("input");
	command.erase(start_pos, 6);
	int n = command[0] - 48;

	// Remove the spaces before the string
	command.erase(0, 2);

	// command just contains the file name now
	Graph *g = read_graph(command);
	graph[n] = g;
	cout << "input successful" << endl;
}

void outputCmd(string command){
	// Remove input from the command string
	int start_pos = command.find("output");
	command.erase(start_pos, 7);
	int n = command[0] - 48;

	// Checks if there is a graph at that location
	if (graph[n] == NULL){
		cout << "output unsuccesful" << endl;
		return;
	}
	
	// Remove the spaces before the string
	command.erase(0, 2);

	// command just contains the file name now
	write_graph(graph[n], command);
	cout << "output successful" << endl;
}

void infoCmd(string command){
	int start_pos = command.find("info");
	command.erase(start_pos, 5);
	int n = command[0] - 48;

	// Checks if there is a graph at that location
	if (graph[n] == NULL){
		cout << "invalid register" << endl;
		return;
	}

	// Display the graph data
	cout << "graph at register " << n;
	cout << " has " << graph[n]->n();
	cout << " vertices, " << graph[n]->e();
	cout << " edges, and "; 

	ParPtrTree *t;
	int comps = components(graph[n], t);
	cout << comps << " components" << endl;
}

void kruskalCmd(string command){
	int start_pos = command.find("kruskal");
	command.erase(start_pos, 8);
	int n = command[0] - 48;
	int m = command[2] - 48;

	ParPtrTree *t;
	int comps = components(graph[n], t);
	if (comps > 1){
		cout << "graph is not connected" << endl;
		return;
	}

	Graph *g = new GraphM(graph[n]->n());
	graph[m] = g;

	Kruskal(graph[n], graph[m]);
}

// This functions job is to disperse the
// commands to the required functions as 
// needed so that each individual command
// line function can be treated as a module
void commandMux(){
	cout << "Enter commands. Enter exit() to quit." << endl;
	string cli_input;
	while(cli_input != "exit()"){
		cout << "$ ";
		getline(cin, cli_input);
		// Make the string lower case
		transform(cli_input.begin(), 
			      cli_input.end(), 
			      cli_input.begin(), 
			      ::tolower);

		if (cli_input.find("input") != string::npos){
			inputCmd(cli_input);
		}
		else if (cli_input.find("output") != string::npos){
			outputCmd(cli_input);
		}
		else if (cli_input.find("info") != string::npos){
			infoCmd(cli_input);
		}
		else if (cli_input.find("kruskal") != string::npos){
			kruskalCmd(cli_input);
		}
		else if (cli_input.find("extract") != string::npos){
			cout << "Running extract" << endl;
		}
		else {
			cout << cli_input << ": command not found" << endl;
		}
	}
}

int main(){
	// Intializing the registers
	// with a couple of graphs
	Graph *g = new GraphM(6);
  	g->setEdge(0,2,7);
    g->setEdge(0,4,9);
    g->setEdge(1,2,5);
    g->setEdge(1,5,6);
    g->setEdge(2,3,1);
    g->setEdge(2,4,3);
    g->setEdge(3,5,2);
    g->setEdge(4,5,1);

    Graph *h = new GraphM(6);
    h->setEdge(4,5,2);
    h->setEdge(1,2,5);
    h->setEdge(1,5,3);
    h->setEdge(2,3,4);
    h->setEdge(3,1,1);
  	h->setEdge(0,2,1);

    Graph *j = new GraphM(6);
    j->setEdge(1,5,2);
  	j->setEdge(0,2,7);
    j->setEdge(4,5,3);
    j->setEdge(1,2,2);
    j->setEdge(3,4,1);
    j->setEdge(2,4,9);
    j->setEdge(2,3,5);

    graph[0] = g;
    graph[1] = h;
    graph[2] = j;

    commandMux();

    delete g;
    delete h;
    delete j;
	return 0;
}