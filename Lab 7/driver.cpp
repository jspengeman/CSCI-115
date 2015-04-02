#include <iostream>
#include "Huffman.h"
using namespace std;

int main(){
	// int arr[20] = {50, 45, 40, 35, 30, 25, 20};
	// heap<int, Min> *TestHeap = new heap<int, Min>(arr, 7, 20);
	// TestHeap->viewHeap();
	// cout << TestHeap->removefirst() << endl;
	// cout << TestHeap->removefirst() << endl;
	// cout << TestHeap->removefirst() << endl;
	// cout << TestHeap->removefirst() << endl;
	// cout << endl;
	// TestHeap->viewHeap();
	
	
	HuffTree<char>* test[8];
    test[0] = new HuffTree<char> ('z', 2);
    cout << test[1] << endl;
    test[1] = new HuffTree<char> ('k', 30);
    test[2] = new HuffTree<char> ('m', 24);
    test[3] = new HuffTree<char> ('c', 32);
    test[4] = new HuffTree<char> ('u', 37);
    test[5] = new HuffTree<char> ('d', 42);
    test[6] = new HuffTree<char> ('l', 42);
    test[7] = new HuffTree<char> ('e', 120);

    HuffTree<char>* final = buildHuff (test, 8);
	return 0;
}