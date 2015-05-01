#include "graph.h"

class AdjGraph : public Graph {
private:
	int numVertex, numEdge;
	int* edges;
	int* mark;
public:	
	AdjGraph(int numVert);
	~AdjGraph();
	void Init(int n);
	int n();
	int e();
	int first(int v);
	int next(int v, int w);
	void setEdge(int v1, int v2, int wght);
	void delEdge(int v1, int v2);
	bool isEdge(int i, int j);
	int weight(int v1, int v2);
	int getMark(int v);
	void setMark(int v, int val);
	Graph *read_graph(string filename);  
	bool write_graph(Graph *g, string filename); 
	int calculate_edge(int vertex1, int vertex2);
};


