#include <iostream>
#include <string>
#include <locale> 
#include <map>
#include <array>
#include <vector>
#include "heap.h"
#include "huffman.h"
using namespace std;

template <typename E> 
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
	heap<HuffTree<E>*, Min>* forest = new heap<HuffTree<E>*, Min>(TreeArray, count, count);
	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
		while (forest->size() > 1) {
			temp1 = forest->removefirst(); 
			temp2 = forest->removefirst(); 
			temp3 = new HuffTree<E>(temp1, temp2);
			forest->insert(temp3); 
			delete temp1; 
			delete temp2; 
	}
	return temp3;
}

void insertFreqs(){
	HuffTree<char> *TreeArray [100];

	map<char, int> frequencies;
	char treeChar;
	string wgt;
	int weight;
	char ctrl = 'y';

	while(ctrl == 'y'){
		cout << "Enter a char: " << endl;
		cin >> treeChar;

		cout << "Enter a frequency: " << endl;
		cin >> wgt;
		int numFreq = stoi(wgt, nullptr, 10);

		frequencies.insert(pair<char, int>(treeChar, numFreq));

		while(true){
			cout << "Enter another (y/n): ";
			cin >> ctrl;

			if (ctrl == 'y' || ctrl == 'n'){
				break;
			}
			else {
				cout << "Invalid" << endl;
			}
		} 
	}

	int count = 0;
	map<char, int>::iterator it;
	for (it = frequencies.begin(); it != frequencies.end(); it++){
    	cout << it->first << ' ' << it->second << endl;
    	HuffTree<char> *newTree = new HuffTree<char>(it->first, it->second);
    	TreeArray[count] = newTree;
    	count++;	
	}
	buildHuff(TreeArray, 100);
}



// HuffTree<char> *tempTree = new HuffTree<char>(treeChar, freq); 
// TreeArray.at(count) = *tempTree;
// cout << TreeArray.length() << endl;
// count++;
