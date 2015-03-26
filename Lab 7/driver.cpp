#include <iostream>
#include "heap.h"
using namespace std;

int main(){
	int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	heap<int, Max> *TestHeap = new heap<int, Max>(arr, 10, 20);
	TestHeap->viewHeap();
	TestHeap->isHeap();
	TestHeap->insert(15);
	TestHeap->insert(14);
	TestHeap->insert(13);
	TestHeap->insert(12);
	TestHeap->insert(11);
	cout << endl;
	TestHeap->viewHeap();
	TestHeap->isHeap();
	return 0;
}