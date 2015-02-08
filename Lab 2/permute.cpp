#include <iostream>
#include <vector>

using namespace std;
void permute(int n);
void permute_prime(vector<int> list, int start);

int main(){
	int n;
	cout << "Enter an integer: ";
	cin >> n;
	permute(n);
}

void permute(int n){
	// Declare and intialize the set
	vector<int> list;
	for (int i = 0; i < n; i++){
		list.push_back(i + 1);
	}

	permute_prime(list, 0);
}

void permute_prime(vector<int> list, int start){
	cout << "start: " << start << endl;
	if (start == list.size()) return;

	int i = start;
	while (i < list.size()){
		cout << list[i] << " ";
		// display right elements of the set
		for (int x = i + 1; x < list.size(); x++){
			cout << list[x] << " ";
		}
		
		// display left elements of the set
		for (int y = i - 1; y >= 0; y--){
			cout << list[y] << " ";
		}
		cout << endl;

		i++;
	}
	
	permute_prime(list, start + 1);  
};

