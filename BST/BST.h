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
			count = 1;
		};

		void InsertNode(int data){
			count++;
			Node* curr = root;
			Node* new_node = new Node(data);
			new_node->LeftChild = NULL;
			new_node->RightChild = NULL;

			while (curr != NULL){
				// If data is less then curr root go left
				if (curr->data > data){
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
				else if (curr->data < data){
					// If NULL make child
					if (curr->RightChild == NULL){
						curr->RightChild = new_node;
						break;
					}
					// If not NULL iterate forward
					else {
						curr = curr->LeftChild;
					}
				}
			}
		};

		bool FindNode(int data){
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
		};

		int count;
		Node* root;
};