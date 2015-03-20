#include <iostream>
#include "BST.h"

using namespace std;

int main(){
	BST *bst = new BST();
	bst->InsertNode(100);
	bst->InsertNode(200);
	bst->InsertNode(50);
	bst->InsertNode(25);
	bst->InsertNode(75);
	bst->InsertNode(150);
	bst->InsertNode(300);
	cout << bst->FindNode(100) << endl;
	cout << bst->FindNode(125) << endl;
	cout << bst->FindNode(1) << endl;
	cout << bst->FindNode(10) << endl;
	bst->printTree(bst->getRoot());
	cout << bst->kthSmallest(1) << endl;
	return 0;
}