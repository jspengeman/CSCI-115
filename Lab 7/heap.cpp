#include <iostream>
#include "heap.h"
using namespace std;

template <typename E>
heap::heap(E* h, int num, int max){ 
	Heap = h; 
	n = num; 
	maxsize = max; 
	buildHeap(); 
}

int heap::size() const { 
	return n; 
}

bool heap::isLeaf(int pos) const { 
	return (pos >= n/2) && (pos < n); 
}

int heap::leftchild(int pos) const { 
	return 2*pos + 1; 
} 

int heap::rightchild(int pos) const { 
	return 2*pos + 2; 
} 

int heap::parent(int pos) const { 
	return (pos-1)/2; 
}

void heap::buildHeap() { 
	for (int i=n/2-1; i>=0; i--) sink(i); 
}

template <typename E>
void heap::insert(const E& it) {
	if (n > maxsize) return;
	int curr = n++;
	Heap[curr] = it; 
	swim(curr);
}

void heap::viewHeap(){
	for (int i = 0; i < n; i++){
		cout << Heap[i] << endl;
	}
	cout << endl;
}

template <typename E>
void heap::swap(int pos1, int pos2){
	E temp = Heap[pos1];
	Heap[pos1] = pos2;
	Heap[pos2] = temp;
}

void heap::sink(int pos) {
	while (!isLeaf(pos)) { 
		int j = leftchild(pos); int rc = rightchild(pos);
		if ((rc < n) && (Heap[rc] < Heap[j])) j = rc; 
		if (Heap[pos] < Heap[j]) return;
		swap(pos, j);
		pos = j; 
	}
}

void heap::swim(int curr){
	while ((curr!=0) && (Heap[curr] < Heap[parent(curr)])) {
		swap(Heap, curr, parent(curr));
		curr = parent(curr);
	}
}