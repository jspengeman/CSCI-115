#include <iostream>
using namespace std;

// Basic constructor that reads 
// in an array and heapifys it
template <typename E, typename Comp>
heap<E, Comp>::heap(E* h, int num, int max){ 
	Heap = h; 
	n = num; 
	maxsize = max; 
	buildHeap(); 
}

// Just returns the size
template <typename E, typename Comp>
int heap<E, Comp>::size() const { 
	return n; 
}

// Checks if the node is a leaf or not
// All leaf nodes are inbetween n/2 and n
template <typename E, typename Comp>
bool heap<E, Comp>::isLeaf(int pos) const { 
	return (pos >= n/2) && (pos < n); 
}

// Gets the elements left child
template <typename E, typename Comp>
int heap<E, Comp>::leftchild(int pos) const { 
	return 2*pos + 1; 
} 

// Gets the elements right child
template <typename E, typename Comp>
int heap<E, Comp>::rightchild(int pos) const { 
	return 2*pos + 2; 
} 

// Gets the elements parent
template <typename E, typename Comp>
int heap<E, Comp>::parent(int pos) const { 
	return (pos-1)/2; 
}

// Builds the heap by calling sink on all nodes
// that are not already leaf nodes
template <typename E, typename Comp>
void heap<E, Comp>::buildHeap() { 
	for (int i=(n/2)-1; i >= 0; i--) sink(i); 
}

// Inserts using the swim method to put it where
// the element should belong
template <typename E, typename Comp>
void heap<E, Comp>::insert(const E& it) {
	if (n > maxsize) return;
	int curr = n++;
	Heap[curr] = it;
	swim(curr);
}

// Trivial swap method, specifically bad to work with this heap
template <typename E, typename Comp>
void heap<E, Comp>::swap(int pos1, int pos2){
	E temp = Heap[pos1];
	Heap[pos1] = Heap[pos2];
	Heap[pos2] = temp;
}

// Compares the parent with either one of the children
// whichever child should come before and swaps it with
// that child if it should come before it
template <typename E, typename Comp>
void heap<E, Comp>::sink(int pos) {
	while (!isLeaf (pos)) {
        int j = leftchild (pos);
        int rc = rightchild (pos);
        if ((rc < n) && Comp::prior (Heap[rc], Heap[j])) { j = rc; }
        if (Comp::prior (Heap[pos], Heap[j])) { return; }
        swap (pos, j);
        pos = j;
	}
}

// Swims the node up to its correct position in the tree
// By comparing it with its parent
template <typename E, typename Comp>
void heap<E, Comp>::swim(int curr){
	while ((curr != 0) && (Comp::prior(Heap[curr], Heap[parent(curr)]))) {
        swap (curr, parent(curr));
        curr = parent(curr);
    }
}

// Simple method to view the heap
// This method will print out the item
// at each index in the heap. Note if
// its an object it must over ride << 
template <typename E, typename Comp>
void heap<E, Comp>::viewHeap(){
	cout << "Size: " << n << endl; 
	for (int i = 0; i < n; i++){
		cout << Heap[i] << endl;
	}
	isHeap();
}

// Basic method to test the heap invariants
// If its not a full tree it fails
// If any leaf should come prior then its parent it fails
template <typename E, typename Comp>
bool heap<E, Comp>::isHeap(){
	for (int i = 0; i <= (n/2)-1; i++){
		int lc = leftchild(i); int rc = rightchild(i);
		cout << "(P, LC, RC) := (" << Heap[i] << ", " << Heap[lc] << ", " << Heap[rc] << ")" << endl;
		if (Comp::prior(Heap[lc], Heap[i]) || Comp::prior(Heap[rc], Heap[i])){
			cout << "Not a heap" << endl;
			return false;
		}
	}
	cout << "Is a heap" << endl;
	return true;
}

// Returns and removes the first element from the heap
template <typename E, typename Comp>
E heap<E, Comp>::removefirst(){
	E output = Heap[0];
	swap(0, --n);
	sink(0);
	return output;
}
