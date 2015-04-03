#include <iostream>
#include "Huffman.h"
using namespace std;

int main(){
	HuffTree<char>* huff_trees[10];
    huff_trees[0] = new HuffTree<char> ('z', 10);
    huff_trees[1] = new HuffTree<char> ('k', 30);
    huff_trees[2] = new HuffTree<char> ('m', 24);
    huff_trees[3] = new HuffTree<char> ('c', 32);
    huff_trees[4] = new HuffTree<char> ('u', 45);
    huff_trees[5] = new HuffTree<char> ('d', 23);
    huff_trees[6] = new HuffTree<char> ('g', 12);
    huff_trees[7] = new HuffTree<char> ('e', 128);
    huff_trees[8] = new HuffTree<char> ('l', 18);
    huff_trees[9] = new HuffTree<char> ('a', 120);

    HuffTree<char>* final = buildHuff (huff_trees, 10);
    cout << final->weight() << endl;
	return 0;
}