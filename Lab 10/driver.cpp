#include <iostream>
#include "graphm.h"
#include "ParPtrTree.h"
#include "heap.cpp"
#include <string>

using namespace std;

int main(){
	// cout << "Enter file name for graph input" << endl;
	// cout << "It should be a csv where each row" << endl;
	// cout << "Please include the file extension" << endl;
	// cout << "is formatted like this: v1,v2,wt: ";
	// string input_file;
	// cin >> input_file; 
	// Graph *graph = read_graph(input_file);
	Graph *graph = read_graph("input.csv");
	cout << "Graph tests" << endl;
	cout << "isEdge tests" << endl;
	cout << graph->isEdge(1, 2) << endl;
	cout << graph->isEdge(2, 3) << endl;
	cout << graph->isEdge(1, 3) << endl;
	cout << graph->isEdge(2, 4) << endl;
	cout << graph->isEdge(3, 4) << endl;

	cout << "weight tests" << endl;
	cout << graph->weight(1, 2) << endl;
	cout << graph->weight(2, 3) << endl;
	cout << graph->weight(1, 3) << endl;
	cout << graph->weight(2, 4) << endl;
	cout << graph->weight(3, 4) << endl;

	cout << "setEdge/delEdge tests" << endl;
	graph->setEdge(5, 1, 30);
	cout << graph->isEdge(1, 5) << endl;
	graph->delEdge(5, 1);
	cout << graph->isEdge(1, 5) << endl;
	graph->setEdge(6, 3, 45);
	cout << graph->isEdge(6, 3) << endl;
	graph->delEdge(6, 3);
	cout << graph->isEdge(6, 3) << endl;

	cout << "first tests" << endl;
	cout << graph->first(1) << endl;
	cout << graph->first(4) << endl;
	cout << graph->first(3) << endl;

	cout << "next tests" << endl;
	cout << graph->next(1, 2) << endl;
	cout << graph->next(3, 2) << endl;
	cout << graph->next(2, 1) << endl;

	cout << "Write graph test, check your local file "; 
	cout << "systems current directory for output.csv" << endl;
	GraphM *w_graph = new GraphM(3);
	w_graph->setEdge(1, 2, 1);
	w_graph->setEdge(1, 3, 5);
	w_graph->setEdge(1, 4, 5);
	write_graph(w_graph, "output.csv");

	cout << "Heap tests" << endl;
	int arr[15] = {5, 4, 3, 2, 1, 10, 9, 8, 7, 6};
	heap<int, Max> *heap = new ::heap<int, Max>(arr, 10, 15);
	cout << "Construction uses sink" << endl;
	heap->viewHeap();
	cout << "isLeaf, parent, left/right child tests" << endl;
	cout << heap->isLeaf(0) << endl;
	cout << heap->isLeaf(9) << endl;
	cout << heap->parent(9) << endl;
	cout << heap->leftchild(0) << endl;
	cout << heap->rightchild(0) << endl;
	cout << "Inserting uses swim" << endl;
	heap->insert(15);
	heap->insert(12);
	heap->insert(13);
	heap->insert(16);
	heap->viewHeap();

	/* The array sets creates three different sets
	 * or trees depending on how we are talking about
	 * them. The trees are instantiated to a tree with
	 * root zero with children nodes of 1 and 2. Then
	 * the second tree with root 3 with children 4 and 5
	 * then with a tree with root 6 and child 7, child 7
	 * has node 8 as a child and node 8 has node 9 as a
	 * child. This will later be used to demonstrate path
	 * compression.
	 *
	 * You can view the union process below as the indexs 
	 * begin to switch because the roots are now changing.
	 */
	cout << "ParPtrTree tests" << endl;
	int sets[10] = {-1, 0, 0, -1, 3, 3, -1, 6, 7, 8};
	ParPtrTree *par_ptr_tree = new ParPtrTree(sets, 10);
	par_ptr_tree->viewTree();
	
	/* This test uses to tree roots
	 * Which does not cause path compression
	 * since there is never a chance to compress
	 */
	par_ptr_tree->UNION(3, 6);
	par_ptr_tree->viewTree();

	/* This test uses a node and a tree root
	 * Which will cause path compression because
	 * the find goes through each node to get to
	 * the root. Creating compression from node 9
	 */ 
	par_ptr_tree->UNION(1, 9);
	par_ptr_tree->viewTree();

	/* This test uses two nodes that are already
	 * in the same test. This was my favorite case
	 * because even though they are already in the 
	 * same set path compression takes place because
	 * the operation to check if they are in different
	 * sets uses the FIND method with compresses the 
	 * graph and makes it even more shallow. You will
	 * notice that nodes 1 and 2 now point to the 
	 * root node (3) after the union fails.
	 */
	par_ptr_tree->UNION(1, 9);
	par_ptr_tree->UNION(2, 9);
	par_ptr_tree->viewTree();
	return 0;
}