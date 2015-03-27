#include <iostream>
using namespace std;

class Max {
public:
    template <typename T>
    static bool prior (T a, T b) {
        return a > b;
    }
};

class Min {
public:
    template <typename T>
    static bool prior (T a, T b) {
        return a < b;
    }
};

template <typename E, typename Comp>
heap<E, Comp>::heap(E* h, int num, int max){ 
	Heap = h; 
	n = num; 
	maxsize = max; 
	buildHeap(); 
}

template <typename E, typename Comp>
int heap<E, Comp>::size() const { 
	return n; 
}

template <typename E, typename Comp>
bool heap<E, Comp>::isLeaf(int pos) const { 
	return (pos >= n/2) && (pos < n); 
}

template <typename E, typename Comp>
int heap<E, Comp>::leftchild(int pos) const { 
	return 2*pos + 1; 
} 

template <typename E, typename Comp>
int heap<E, Comp>::rightchild(int pos) const { 
	return 2*pos + 2; 
} 

template <typename E, typename Comp>
int heap<E, Comp>::parent(int pos) const { 
	return (pos-1)/2; 
}

template <typename E, typename Comp>
void heap<E, Comp>::buildHeap() { 
	for (int i=(n/2)-1; i >= 0; i--) sink(i); 
}

template <typename E, typename Comp>
void heap<E, Comp>::insert(const E& it) {
	if (n > maxsize) return;
	int curr = n++;
	Heap[curr] = it;
	swim(curr);
}

template <typename E, typename Comp>
void heap<E, Comp>::swap(int pos1, int pos2){
	E temp = Heap[pos1];
	Heap[pos1] = Heap[pos2];
	Heap[pos2] = temp;
}

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

template <typename E, typename Comp>
void heap<E, Comp>::swim(int curr){
	while ((curr != 0) && (Comp::prior(Heap[curr], Heap[parent(curr)]))) {
        swap (curr, parent(curr));
        curr = parent(curr);
    }
}

template <typename E, typename Comp>
void heap<E, Comp>::viewHeap(){
	cout << "Size: " << n << endl; 
	for (int i = 0; i < n; i++){
		cout << Heap[i] << endl;
	}
	isHeap();
}

template <typename E, typename Comp>
bool heap<E, Comp>::isHeap(){
	for(int i = 0; i < n; i++){
		int lc = leftchild(i); int rc = rightchild(i);
		if (!isLeaf(i)){
			cout << "Parent: " << Heap[i] << ", Left child: " << Heap[lc] << ", Right child: " << Heap[rc] << endl;
			if (Comp::prior(Heap[lc], Heap[i]) || Comp::prior(Heap[rc], Heap[i])){
				cout << "Not a heap" << endl;
				return false;
			}
		}
	}
	cout << "Is a heap" << endl;
	return true;
}

template <typename E, typename Comp>
E heap<E, Comp>::removefirst(){
	E output = Heap[0];
	swap(0, --n);
	sink(0);
	return output;
}
