// ToDo: Create > and < overloaded operators for the huffman coding tree
#include <iostream>
using namespace std;

template <typename E>
heap<E>::heap(E* h, int num, int max){ 
	Heap = h; 
	n = num; 
	maxsize = max; 
	buildHeap(); 
}

template <typename E>
int heap<E>::size() const { 
	return n; 
}

template <typename E>
bool heap<E>::isLeaf(int pos) const { 
	return (pos >= n/2) && (pos < n); 
}

template <typename E>
int heap<E>::leftchild(int pos) const { 
	return 2*pos + 1; 
} 

template <typename E>
int heap<E>::rightchild(int pos) const { 
	return 2*pos + 2; 
} 

template <typename E>
int heap<E>::parent(int pos) const { 
	return (pos-1)/2; 
}

template <typename E>
void heap<E>::buildHeap() { 
	for (int i=(n/2)-1; i >= 0; i--) sink(i); 
}

template <typename E>
void heap<E>::insert(const E& it) {
	if (n > maxsize) return;
	int curr = n++;
	Heap[curr] = it; 
	swim(curr);
}

template <typename E>
void heap<E>::viewHeap(){
	for (int i = 0; i < n; i++){
		cout << Heap[i] << endl;
	}
}

template <typename E>
void heap<E>::swap(int pos1, int pos2){
	E temp = Heap[pos1];
	Heap[pos1] = Heap[pos2];
	Heap[pos2] = temp;
}

template <typename E>
void heap<E>::sink(int pos) {
	while (!isLeaf(pos)) { 
		int j = leftchild(pos); int rc = rightchild(pos);
		if ((rc < n) && (Heap[rc] < Heap[j])) j = rc; 
		if (Heap[pos] < Heap[j]) return;
		swap(pos, j);
		pos = j; 
	}
}

template <typename E>
void heap<E>::swim(int curr){
	while ((curr!=0) && (Heap[curr] < Heap[parent(curr)])) {
		swap(curr, parent(curr));
		curr = parent(curr);
	}
}
