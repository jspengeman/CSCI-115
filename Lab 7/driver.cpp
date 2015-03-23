#include <iostream>
#include "heap.h"
using namespace std;

int main(){
	int arry[10] = {50, 20, 75, 90, 100, 80, 110, 25};
	heap<int> *TestHeap = new heap<int>(arry, 10, 10);
	TestHeap->viewHeap();
	return 0;
}