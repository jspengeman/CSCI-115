#include <iostream>
#include "BST.h"
using namespace std;

BST::BST(){
	root = NULL;
	count = 0;
}

void BST::printTree(Node *root){
	// Prints the tree from highest values to lowest values
	if (root == NULL) return; 
	printTree(root->RightChild);
	cout << "Node: " << root->data << endl;
	cout << "Count: " << root->nodeCount << endl;
	printTree(root->LeftChild);
}

void BST::InsertNode(int data){
	count++;
	Node* curr = root;
	Node* new_node = new Node(data);

	if (root == NULL){ 
		root = new_node; 
		return;
	}
	// Iterative insertions, still log(n) time complexity
	while (curr != NULL){
		// If data is less then curr root go left
		curr->nodeCount++;
		if (data < curr->data){
			// If NULL make child
			if (curr->LeftChild == NULL){
				curr->LeftChild = new_node;
				break;
			}
			// If not NULL iterate forward
			else {
				curr = curr->LeftChild;
			}
		}
		// If data is greater then curr root go right
		else if (data > curr->data){
			// If NULL make child
			if (curr->RightChild == NULL){
				curr->RightChild = new_node;
				break;
			}
			// If not NULL iterate forward
			else {
				curr = curr->RightChild;
			}
		}
	}
}

bool BST::FindNode(int data){
	Node *curr = root;

	while (curr != NULL){
		// Checks if current node is target
		if (curr->data == data){
			return true;
		}
		// If data is less then curr data go left
		else if (curr->data > data){
			curr = curr->LeftChild;
		}
		// If data is less then curr data go right
		else if (curr->data < data){
			curr = curr->RightChild;
		}
	}
	return false;
}

int BST::kthSmallest(Node *curr, int k){
	if (curr == NULL) return 0;
	
	// Let j be equal to number of children plus 1
	int j = (curr->LeftChild == NULL) ? 0 : curr->LeftChild->nodeCount;

	if (j == k - 1){
		return curr->data;
	}
	else if (j > k - 1){
		return kthSmallest(curr->LeftChild, k);
	}
	else {
		return kthSmallest(curr->RightChild, k - j - 1);
	}
}