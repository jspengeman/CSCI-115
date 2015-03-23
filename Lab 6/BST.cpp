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
		/*
		 * nodeCount is my invariant. Every time a node passes curr
		 * its node count should be incremented. Leafs nodeCount=1.
		 * Base case: assume we have an empty tree T, and we insert
		 * node N into T then N->codeCount == 1. 
		 * N + 1 case: the number of elements in a tree are equal to
		 * 1 + leftSubtree + rightSubtree. If a node is inserted into 
		 * a tree it is either in the right or left subtree. 
		 * countNodes(root) + n == countNodes(insert(value))
		 * where n is equal to the number of nodes being inserted
		 * if this is true for 0 and n then it will be true for n+1 
		 * and so on.
		 */
		curr->nodeCount++;

		// If data is less then curr root go left
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
	// Wrote this method to test the tree invariants

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
	while(curr !=NULL){
		int j = (curr->LeftChild == NULL) ? 0 : curr->LeftChild->nodeCount;

		// If j equals k-1 then it is the currents nodes value
		if (j == k - 1){
			return curr->data;
		}
		// If j is greater then k-1 then it must be in the left subtree
		else if (j > k - 1){
			curr = curr->LeftChild;
		}
		// If j is less then k then it must be in the right subtree
		// We no longer need to check j+1 nodes so skip those
		else {
			curr = curr->RightChild; 
			k = k - j - 1;
		}
	}
	// Error or nothing was found for that kth value
	return 0;
}

int BST::keysBetween(int start, int end){
	int count = 0;
	int *data = &count;
	keysBetweenPrime(root, start, end, data);
	cout << endl << "Nodes visited: " << count << endl;
	return count;
}

// I couldn't think of a more elegant solution. 
// Time complexity is unfortunately O(N)
// Sadly it visits every node of the tree.
void BST::keysBetweenPrime(Node *curr, int start, int end, int *count){
	if(curr == NULL) return;
	*count+=1;
	keysBetweenPrime(curr->LeftChild, start, end, count);
	if (curr->data >= start && curr->data <= end) cout << curr->data << " ";
	keysBetweenPrime(curr->RightChild, start, end, count);
}