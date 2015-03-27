#include <iostream>
#include <string>
#include <locale> 
#include <map>
#include <array>
#include <algorithm>
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
	array<HuffTree<char>, 100> TreeArray;

	map<char,int> frequencies;
	string temp;
	string aux;
	char treeChar;
	int weight;
	char ctrl = 'y';
	int count = 0;

	while(ctrl == 'y'){
		temp = "";
		cout << "Enter frequencies in the format: char int " << endl;
		getline(cin, temp);
		
		for(int i = 0; i < temp.size(); i++){
			if (isalnum(temp[i])){
				aux.push_back(temp[i]);
			}
		}

		temp = aux;
		string num;
		treeChar = temp[0];
		num = temp.substr(1);
		int numFreq = stoi(num, nullptr, 10);

		frequencies.insert(pair<char,int>(treeChar, numFreq));

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
}



// HuffTree<char> *tempTree = new HuffTree<char>(treeChar, freq); 
// TreeArray.at(count) = *tempTree;
// cout << TreeArray.length() << endl;
// count++;
