#include <iostream>
#include "heap.h"
#include "huffman.h"
using namespace std;

int main(){
	int arr[20] = {50, 45, 40, 35, 30, 25, 20, 15, 10, 5};
	heap<int, Min> *TestHeap = new heap<int, Min>(arr, 10, 20);
	TestHeap->viewHeap();
	// TestHeap->insert(1);
	// TestHeap->insert(2);
	// TestHeap->insert(3);
	// TestHeap->insert(4);
	// TestHeap->insert(5);
	// cout << TestHeap->removefirst() << endl;
	// cout << TestHeap->removefirst() << endl;
	// cout << TestHeap->removefirst() << endl;
	return 0;
}