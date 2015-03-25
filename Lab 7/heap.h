template <typename E> class heap {
private:
	E* Heap; 
	int maxsize; 
	int n; 

	void swap(int pos1, int pos2);
	void sink(int pos);
	void swim(int pos);
public:
	heap(E* h, int num, int max);
	int size() const;
	bool isLeaf(int pos) const;
	int leftchild(int pos) const;
	int rightchild(int pos) const;
	int parent(int pos) const;
	void buildHeap();
	void insert(const E& it);
	void viewHeap();
};

// I know this is bad but with out it I would
// have to declare the template class name
// for each type I want to use in heap.cpp
#include "heap.cpp"