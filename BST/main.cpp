#include <iostream>
#include "BST.h"

using namespace std;

int main(){
	int x = 5;
	BST bst(x);
	bst.InsertNode(3);
	bst.InsertNode(6);
	cout << bst.root->data << endl;
	cout << bst.root->LeftChild->data << endl;
	cout << bst.root->RightChild->data << endl;
	cout << bst.FindNode(2) << endl;
	return 0;
}