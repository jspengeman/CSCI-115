#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
void swap(int &i, int &j);
void permute(int n, int i);
void std_permute(vector<int> list);

int *nums;

int main() {
    int n;
    cout << "Enter an integer: ";
    cin >> n;
    nums = new int[n]; 
    
    // Intialize the set of numbers
    for (int i = 0; i < n; i++) { nums[i] = i + 1; }

    permute(n, 0);
    return 0;
}

void std_permute(vector<int> list){
    // Using std::algorithm to implement permutations
    do {
        for (int i = 0; i < list.size(); i++){
            cout << list[i] << " ";
        }
        cout << endl;
    } while (std::next_permutation(list.begin(), list.end()));
}

void permute(int n, int i){
    // Using my own implementation for permutations
    if (i == n - 1) {
        int j = 0;
        // Display current permutation
        while (j < n) {
            cout << nums[j] << " ";
            j++;
        }    
    cout << endl;
    }
    else {
        int j = i;
        // Generate permutation
        while (j < n) {
            swap(nums[i], nums[j]);
            permute(n, i + 1);     
            swap(nums[i], nums[j]);
            j++;
        }
    }
}

void swap(int &i, int &j){
    int t = i;
    i = j;
    j = t;
}
