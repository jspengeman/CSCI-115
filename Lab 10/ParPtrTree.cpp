#include <iostream>
#include "ParPtrTree.h"
// Negative one will be put in place for
// nodes that are going to be roots
#define ROOT -1

using namespace std;

ParPtrTree::ParPtrTree(int n){
	array = new int[n];
	for(int i = 0; i < size; i++)
		array[i] = -99;
	size = n;
}

ParPtrTree::ParPtrTree(int *arr, int n){
	array = arr;
	size = n;
}

int ParPtrTree::FIND(int curr) const {
	if (array[curr] == ROOT) return curr; // At root
	array[curr] = FIND(array[curr]);
	return array[curr];
}

void ParPtrTree::UNION(int i, int j){
	if(differ(i, j)) return;
	int iWeight = 0; int jWeight = 0;
	int iTree = FIND(i); 
	int jTree = FIND(j);

	for(int x = 0; x < size; x++){
		if (array[x] == iTree) iWeight++;
		else if (array[x] == jTree) jWeight++;
	}

	if(iWeight > jWeight){
		array[jTree] = iTree; 
	}
	else {
		array[iTree] = jTree;
	}
}

bool ParPtrTree::differ(int i, int j){
	if(array[i] == -1 && array[j] == -1) return false;
	return array[i] == array[j];
}

void ParPtrTree::viewTree(){
	for(int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}