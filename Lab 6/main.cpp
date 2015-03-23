#include <iostream>
#include "BST.h"

using namespace std;

int main(){
	// Please run using:
	// g++ main.cpp BST.cpp -o main.o
	// or with:
    // g++ -c -o bst.o BST.cpp
	// g++ -c -o main.o main.cpp
	// g++ -o exec bst.o main.o
	BST *bst = new BST();
	bst->InsertNode(100);
	bst->InsertNode(200);
	bst->InsertNode(50);
	bst->InsertNode(25);
	bst->InsertNode(75);
	bst->InsertNode(150);
	bst->InsertNode(300);
	// Correctly inserts nodes
	cout << bst->FindNode(100) << endl;
	cout << bst->FindNode(125) << endl;
	cout << bst->FindNode(1) << endl;
	cout << bst->FindNode(10) << endl;
	bst->printTree(bst->getRoot());
	// Correctly finds the kth Smallest element
	cout << bst->kthSmallest(bst->getRoot(), 1) << endl;
	cout << bst->kthSmallest(bst->getRoot(), 2) << endl;
	cout << bst->kthSmallest(bst->getRoot(), 3) << endl;
	cout << bst->kthSmallest(bst->getRoot(), 4) << endl;
	cout << bst->kthSmallest(bst->getRoot(), 5) << endl;
	cout << bst->kthSmallest(bst->getRoot(), 6) << endl;
	cout << bst->kthSmallest(bst->getRoot(), 7) << endl;
	// Finds the keys between two keys. Ill admit
	// at a poor time complexity though
	bst->keysBetween(100, 300);
	bst->keysBetween(100, 100);
	bst->keysBetween(25, 100);
	bst->keysBetween(75, 150);
	return 0;
}
	