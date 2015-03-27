#include <iostream>
#include "huffman.cpp"
using namespace std;

int main(){
	int arr[20] = {50, 45, 40, 35, 30, 25, 20};
	heap<int, Min> *TestHeap = new heap<int, Min>(arr, 7, 20);
	TestHeap->viewHeap();
	cout << TestHeap->removefirst() << endl;
	cout << TestHeap->removefirst() << endl;
	cout << TestHeap->removefirst() << endl;
	cout << TestHeap->removefirst() << endl;
	cout << endl;
	TestHeap->viewHeap();
	insertFreqs();
	return 0;
}