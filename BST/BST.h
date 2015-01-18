#include <iostream>
using namespace std;

class Node {
	public:
		Node(int data){
			this->data = data;
		};

		int data;
		Node* LeftChild;
		Node* RightChild;
};

class BST {
	public:
		BST(int data){
			Node* new_root = new Node(data);
			root = new_root;
			root->LeftChild = NULL;
			root->RightChild = NULL;
			this.count = 1;
		};

		void InsertNode(int data){
			count++;
			Node* curr = root;
			Node* new_node = new Node(data);
			new_node->LeftChild = NULL;
			new_node->RightChild = NULL;
			
			while (curr != NULL){
				if (curr->data < data){
					if (curr->LeftChild == NULL){
						curr->LeftChild = new_node;
					}
					else {
						curr = curr->LeftChild;
					}
				}
				else if (curr->data > data){
					if (curr->RightChild == NULL){
						curr->RightChild = new_node;
					}
					else {
						curr = curr->LeftChild;
					}
				}
			}
		};

		void FindNode();
		int count;
		Node* root;
};