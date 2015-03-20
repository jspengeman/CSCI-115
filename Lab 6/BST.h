#include <iostream>
using namespace std;

class Node {
public:
	Node(int data){ 
		this->nodeCount = 0;
		this->data = data; 
		this->LeftChild = NULL;
		this->RightChild = NULL;
	};
	int data;
	int nodeCount;
	Node* LeftChild;
	Node* RightChild;

};

class BST {
private:
	int count;
	Node* root;

public:
	BST();
	Node* getRoot(){ return this->root; };
	void printTree(Node *root);
	void InsertNode(int data);
	bool FindNode(int data);
	int getSizeOfLeft(Node *node);
	int kthSmallest(int k);
};
