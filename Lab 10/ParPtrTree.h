// General tree representation for UNION/FIND
class ParPtrTree {
private:
	int* array; // Node array
	int size; // Size of node array
	int FIND(int j) const; // Find root
public:
	ParPtrTree(int n); // Constructor
	~ParPtrTree() { delete [] array; } // Destructor
	void UNION(int i, int j); // Merge equivalences
	bool differ(int i, int j); // True if not in same tree
	void viewTree();
};