#include <iostream>
#include "BST.h"

using namespace std;

int main(){
	int x = 5;
	BST bst(x);
	bst.InsertNode(8);
	cout << bst.root->data << endl;
	cout << bst.root->RightChild->data << endl;
	return 0;
}