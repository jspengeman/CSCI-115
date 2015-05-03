#include <iostream>
#include "ParPtrTree.h"
#define ROOT 0

using namespace std;

ParPtrTree::ParPtrTree(int n){
	array = new int[n];
	for(int i = 0; i < size; i++)
		array[i] = -1;
	size = n;
}

int ParPtrTree::FIND(int curr) const {
	if (array[curr] == ROOT) return curr; // At root
	array[curr] = FIND(array[curr]);
	return array[curr];
}

void ParPtrTree::UNION(int i, int j){
	
}

bool ParPtrTree::differ(int i, int j){
	return array[i] != array[j];
}

void ParPtrTree::viewTree(){
	for(int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}