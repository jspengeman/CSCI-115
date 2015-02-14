#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

void initialize(vector<int> &list, int size){
	for(int i = 0; i < size; i++){
		list.push_back(i);
	}
}

bool sequential(vector<int> &list, int target){
	for (int i = 0; i < list.size(); i++){
		if (target == list[i]){
			return true;
		}
	}
	return false;
}

bool binary(vector<int> &list, int target) {
	int n = list.size();
	int l = -1;
	int r = n; 								
	while (l+1 != r) { 						
			int i = (l+r)/2; 				
			if (target < list[i]) r = i; 			
			if (target == list[i]) return true;
			if (target > list[i]) l = i; 			 
		}
	return false; 								
}

double sequentialTest(vector<int> &list){
	clock_t start = clock();

	srand(time(NULL));
	for (int i = 0; i <= 1000; i++){
		int target = rand();
		sequential(list, target);
	}
	double end = double(clock() - start)/CLOCKS_PER_SEC;
	return end;
}

double binaryTest(vector<int> &list){
	clock_t start = clock();

	srand(time(NULL));
	for (int i = 0; i <= 1000; i++){
		int target = rand();
		binary(list, target);
	}
	double end = double(clock() - start)/CLOCKS_PER_SEC;
	return end;
}

int main(){
	cout << "Enter an Integer: " << endl;
	int x; cin >> x;
	
	int size;
	size = pow(10, x);
	vector<int> list;
	initialize(list, size);
	int target = 5;

	cout << "Size: " << size << endl;
	cout <<"Sequential search time: ";
	cout << sequentialTest(list) << "ms" << endl;

	cout <<"Binary search time: ";
	cout << binaryTest(list) << "ms" << endl;		
}