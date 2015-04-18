#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string>
#include <fstream>

using namespace std;

void swap(int *arr, int x, int y){
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp; 
}

// Had to use unsigned ints here to keep count for the swaps and comps
void insertion(int *arr, int size, unsigned int &swapCount, unsigned int &compCount) {
	for (int i = 1; i < size; i++){
		for (int j = i; j > 0; j--){
			if (arr[j] < arr[j-1]){
				swap(arr, j, j-1);	
				swapCount++;
			}
			compCount++;
		}
	}
}

void bubble(int *arr, int size, unsigned int &swapCount, unsigned int &compCount) {
	for (int i = 0; i < size - 1; i++){
		for (int j = size-1; j > i; j--){
			if (arr[j] < arr[j-1]){
				swap(arr, j, j-1);
				swapCount++;
			}
			compCount++;
		}
	}
}

void selection(int *arr, int size, unsigned int &swapCount, unsigned int &compCount) { 
	for (int i = 0; i < size-1; i++) { 
		int lowindex = i; 
		for (int j = size-1; j > i; j--){ 
			if (arr[j] < arr[lowindex])
				lowindex = j; 
			compCount++;
		}
		swap(arr, i, lowindex);
		swapCount++;
	}
}

void mergesort(int arr[], int temp[], int left, int right, unsigned int &compCount) {
	// Merge sort is unique in the fact that it does no swapping, pretty neat.
	if (left == right) return; 
	int mid = (left+right)/2;
	mergesort(arr, temp, left, mid, compCount);
	mergesort(arr, temp, mid+1, right, compCount);
	
	// Copy subarray to temp
	for(int i=left; i<=right; i++) 
		temp[i] = arr[i];
	
	// Do the merge operation back to arr
	int i1 = left; int i2 = mid + 1;
	for(int curr = left; curr <= right; curr++) {
		if (i1 == mid + 1) 		// Left sublist exhausted
			arr[curr] = temp[i2++];
		else if (i2 > right) 	// Right sublist exhausted
			arr[curr] = temp[i1++];
		else if (temp[i1] < temp[i2])
			arr[curr] = temp[i1++];
		else 
			arr[curr] = temp[i2++];
		compCount++; // One array comparison taking place for each call
	}
}

inline int findpivot(int arr[], int i, int j) { return (i+j)/2; }

inline int partition(int arr[], int l, int r, int& pivot, unsigned int &swapCount, unsigned int &compCount) {
	do { // Move the bounds inward until they meet
		// Move l right and left with these loops
		while (arr[++l] < pivot) compCount++; 
		while ((l < r) && (pivot < arr[--r])) compCount++; 
		swap(arr, l, r); // Swap out of place values
		swapCount++;
	} while (l < r); 
		return l; 
}

void quicksort(int arr[], int i, int j, unsigned int &swapCount, unsigned int &compCount) {
	if (j <= i) return;
	int pivotindex = findpivot(arr, i, j);
	swap(arr, pivotindex, j); 
	int k = partition(arr, i-1, j, arr[j], swapCount, compCount);
	swap(arr, k, j); 
	swapCount += 2; // Increment by two for the two different swaps taking place
	quicksort(arr, i, k-1, swapCount, compCount);
	quicksort(arr, k+1, j, swapCount, compCount);
}

void shuffle(int *arr, int size){
	for (int i = size - 1; i >= 1; i--){
		// Finding a random number that is 
		// within the boundry of 0 <= j <= i
		int j = rand() % i;
		swap(arr, i, j);
	}	
}

// Returns a pointer to an array that has 
// been dynamically allocated and intialized
// with random values from 0 to 10^i - 1
int* intialize(int i){
	int size = pow(10, i);
	int* arr = new int[size];

	for(int j = 0; j < size; j++){
		// Produces a random number from 1 to size
		arr[j] = rand() % size + 1;
	}

	return arr;
}

int* upDownIntialize(bool isUp){
	int* arr = new int[10000];
	int x = 0;
	int y = 9999;

	if(isUp) {
		while(x <= 0){
			arr[x] = x + 1;
			x++;
		}
	}
	else {
		while(y >= 9999){
			arr[y] = y + 1;
			y--;
		}
	}

	return arr;
}

void viewArray(int *arr, int size){
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void getAlgorithmData(unsigned int output[5][16]){
	int *array;
	int size, dataCount;
	unsigned int swapCount, compCount;
	int *temp;
	
	// Call all sorting algorithms for all sizes
	// You will notice that a temp array is 
	// dynamic created as well although it is 
	// only used for the merge sort algorithm
	for(int j = 0; j <= 4; j++){	
		dataCount = 0;
		for(int i = 1; i <= 6; i++){
			swapCount = 0; compCount = 0;
			size = pow(10, i);
			array = intialize(i);
			shuffle(array, size);

			if (j == 3){
				// If mergesort allocate a junk temp array
				temp = intialize(i);
			}

			// Call the desired algorithm here
			// 10k up and down rows will be populated later
			switch(j){
				// case 0: insertion(array, size, swapCount, compCount); break;
				// case 1: bubble(array, size, swapCount, compCount); break;
				// case 2: selection(array, size, swapCount, compCount); break;
				case 3: mergesort(array, temp, 0, size - 1, compCount); break;
				case 4: quicksort(array, 0, size - 1, swapCount, compCount); break;
				default: cout << "Error 1" << endl; break;
			}

			delete array;

			if (j == 3){
				// If mergesort free the junk temp array
				delete temp;
			}

			// Put the data in output array 
			// pairs of (k, k + 1) represent 
			// the swap, comp count tuples
			output[j][dataCount] = swapCount;
			output[j][dataCount + 1] = compCount;
			dataCount += 2;
		}
	}

	// Populates the output with the 10k up and down data
	bool up = true;
	dataCount = 12;	
	size = 10000;
	swapCount = 0; compCount = 0; 
	temp = upDownIntialize(false); // Allocate a junk 10k size temp array
	for(int i = 0; i <= 4; i++){
		array = upDownIntialize(up);
		switch(i){
			case 0: insertion(array, size, swapCount, compCount); break;
			case 1: bubble(array, size, swapCount, compCount); break;
			case 2: selection(array, size, swapCount, compCount); break;
			case 3: mergesort(array, temp, 0, size - 1, compCount); break;
			case 4: quicksort(array, 0, size - 1, swapCount, compCount); break;
			default: cout << "Error 2" << endl; break;
		}
		delete array;

		cout << endl;
		cout << i << " : " << swapCount;
		cout << endl;

		output[i][dataCount] = swapCount;
		output[i][dataCount + 1] = compCount;


		// Start over the loop but this time for the 
		// 10 k down values this will not create an
		// infinite loop and will only restart it once
		if (i == 4 and up){
			dataCount = 14;
			up = false;
			i = -1; // Set to negative one because it needs to be zero on next loop
		}
	}
}

void displayData(unsigned int output[5][16]){
	for (int i = 0; i < 5; i++){
		switch(i){
			case 0: cout << "Insertion: " << endl; break;
			case 1: cout << "Bubble: " << endl; break;
			case 2: cout << "Selection: " << endl; break;
			case 3: cout << "Merge: " << endl; break;
			case 4: cout << "Quick: " << endl; break;
			default: cout << "Error 3" << endl; break;
		}
		for (int j = 0; j < 15; j+= 2){
			switch(j){
				case 0: cout << "10: "; break;
				case 2: cout << "100: "; break;
				case 4: cout << "1,000: "; break;
				case 6: cout << "10,000: "; break;
				case 8: cout << "100,000: "; break;
				case 10: cout << "1,000,000: "; break;
				case 12: cout << "10k up: "; break;
				case 14: cout << "10K down: "; break;
				default: cout << "Error 4" << endl; break;
			}

			cout << output[i][j] << ",";
			cout << output[i][j + 1] << endl;
		}
		cout << endl;
	}
}

void createOuputCSV(unsigned int output[5][16]){
	cout << "Please check your local file system's current directory for";
	cout << " a copy of output.csv, please note you will need to space out";
	cout << " the columns of the spread sheet yourself" << endl;

	ofstream output_file;
	output_file.open("output.csv");
	// Declare header row of file
	output_file << "Algorithm, 10, 100, 1000, 10000, 100000, 1000000, 10K Up, 10K Down \n";
	for (int i = 0; i < 5; i++){
		switch(i){
			case 0: output_file << "Insertion,"; break;
			case 1: output_file << "Bubble,"; break;
			case 2: output_file << "Selection,"; break;
			case 3: output_file << "Merge,"; break;
			case 4: output_file << "Quick,"; break;
			default: cout << "Error 3" << endl; break;
		}

		// Swaps and comps are seperated by /
		for(int j = 0; j < 15; j+= 2){
			output_file << output[i][j];
			output_file << "/";
			output_file << output[i][j + 1] << ",";		
		}
		output_file << "\n";
	}
	output_file.close();
}

int main(){
	// Output for the swap and compares
	unsigned int output[5][16];

	// Intializing random number generator
	srand(time(NULL));
	// Call function that calls all sorts
	getAlgorithmData(output);
	// Display all of the sorting alg data
	displayData(output);
	createOuputCSV(output);

	return 0;
}