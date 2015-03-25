#include <iostream>
#include "heap.h"
using namespace std;

int main(){
	int arr[10] = {50, 20, 30, 10, 60, 70, 80, 90, 100};
	heap<int> *TestHeap = new heap<int>(arr, 9, 10);
	TestHeap->viewHeap();
	TestHeap->insert(10);
	return 0;
}