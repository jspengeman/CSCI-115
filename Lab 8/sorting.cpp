#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string>
#include <sstream>
#include <iomanip>

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

void bubble(int *arr, int size, int &swapCount, int &compCount) {
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

void selection(int *arr, int size, int &swapCount, int &compCount) { 
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

void mergesort(int arr[], int temp[], int left, int right, int &compCount) {
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

inline int partition(int arr[], int l, int r, int& pivot, int &swapCount, int &compCount) {
	do { // Move the bounds inward until they meet
		// Move l right and left with these loops
		while (arr[++l] < pivot) compCount++; 
		while ((l < r) && (pivot < arr[--r])) compCount++; 
		swap(arr, l, r); // Swap out of place values
		swapCount++;
	} while (l < r); 
		return l; 
}

void quicksort(int arr[], int i, int j, int &swapCount, int &compCount) {
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

void viewArray(int *arr, int size){
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void getInsertionData(unsigned int output[5][16]){
	// Index zero represents insertion sort data
	int *array;
	int size, dataCount;
	unsigned int swapCount, compCount;

	dataCount = 0;
	// TODO: change this back to i <= 6
	for(int i = 1; i <= 5; i++){
		swapCount = 0; compCount = 0;
		size = pow(10, i);
		array = intialize(i);
		shuffle(array, size);
		insertion(array, size, swapCount, compCount);

		// Put the data in output array 
		// pairs of (k, k + 1) represent 
		// the swap, comp count tuples
		output[0][dataCount] = swapCount;
		output[0][dataCount + 1] = compCount;
		dataCount += 2;
	}

	// TODO: Do the 10k up and 10k down here
}

void displayData(unsigned int output[5][16]){
	const char separator = ' ';
   	int nameWidth = 10;
    int numWidth = 15;

    cout << left << setw(nameWidth) << setfill(separator) << "Algorithm";
    cout << left << setw(nameWidth) << setfill(separator) << "10";
    cout << left << setw(numWidth) << setfill(separator) << "100";
    cout << left << setw(numWidth) << setfill(separator) << "1,000";
    cout << left << setw(numWidth) << setfill(separator) << "10,000";
    cout << left << setw(numWidth) << setfill(separator) << "100,000";
    cout << left << setw(numWidth) << setfill(separator) << "1,000,000";
    cout << left << setw(numWidth) << setfill(separator) << "10K Up";
    cout << left << setw(numWidth) << setfill(separator) << "10K Down";
    cout << endl;

    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << left << setw(numWidth) << setfill(separator) << "----------";
    cout << endl;

    nameWidth = 40;
    numWidth = 50;

	string algs[5] = {
		"Insertion", "Bubble", "Selection",
		"Merge", "Quick"
	};

	stringstream str_s;
	string outStr;
	// TODO: change this to i < 5
	for (int i = 0; i < 1; i++){
		cout << left << setw(nameWidth) << setfill(separator) << algs[i];
		for (int j = 0; j < 12; j+= 2){

			str_s << output[i][j];
			str_s << ",";
			str_s << output[i][j + 1];
			outStr = str_s.str();

			cout << left << setw(nameWidth) << setfill(separator) << outStr;
		}
		cout << endl;
	}
}

int main(){
	// Output for the swap and compares
	unsigned int output[5][16];

	// Intializing random number generator
	srand(time(NULL));
	getInsertionData(output);
	displayData(output);

	return 0;
}