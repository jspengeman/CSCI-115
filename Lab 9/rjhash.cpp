#include <iostream>
#include <fstream>
#include <array>
#include <math.h> 
#define HASHSIZE 4001

using namespace std;

struct keyValue
{
	string key;
	int value;
};

class Hash {
private:
	array<keyValue, HASHSIZE> data;
	array<int, HASHSIZE> updates;
	array<int, HASHSIZE> cost;
	int c_size;
	int curr;

public:
	Hash(){
		for(int i = 0; i < HASHSIZE; i++){
			data[i].key = "";
			data[i].value = 0;
			updates[i] = 0;
			cost[i] = 0;
		}
		c_size = 0;
		curr = -1;
	}
	int size(){ return c_size; };
	void reset(){ curr = -1; }
	int count(int index){ return data[index].value; }
	int probes(){ return cost[c_size - 1]; } // Double check this
	int p(int i){ return pow(i, 2); } // Quadratic probing

	void update(char *key){
		int addr_value = 0;
		string addr_key = "";
		int index = sfold(key);
		string str_key = string(key);
		// Increment the number of updates for current size
		updates[c_size]++; 

		cout << index << endl;
		cout << c_size << endl;
		// Check if the string is not empty
		if (data[index].key != ""){
			// Check if the string is the same
			if (data[index].key == str_key){
				data[index].value++;
			}
			// String is different, do probing
			else {
				// Establish home element
				string home = data[index].key;
				// First probe index
				int new_index = p(index);
				new_index = new_index % HASHSIZE;

				string curr = data[new_index].key;

				// Infinite loop due to the probing method being used
				// It is looping because it never goes directly back 
				// to home which is being used as the looping sentinel

				// Doing probing here
				while(home != curr){	
					// If current element is occupied
					if (data[new_index].key != ""){
						new_index = p(new_index);
						new_index = new_index % HASHSIZE;
						// Change curr to new value
						curr = data[new_index].key;
						// Costs is incremented before the size is incremented
						cost[c_size]++;
					}
					// Current element isn't occupied
					// Set value at this index
					else {
						data[new_index].key = str_key;
						data[new_index].value++;
						c_size++;
						return;
					}
				}
				c_size++;
			}
		}
		else {
			// String is empty. Create new (key, value) pair
			data[index].key = str_key;
			data[index].value++;
			c_size++;
		}
	}

	void next(string &key, int &value){
		// Looking for the next element
		int i = curr;
		while(i < HASHSIZE){
			if (data[i].key == ""){
				key = data[i].key;
				value = data[i].value;
				return;
			}
			i++;
		}

		// Setting not found return values
		if (i + 1 == HASHSIZE){
			key = "";
			value = -1;
		}
	}

	int sfold(char* key) {
		unsigned int *lkey = (unsigned int *)key;
		int intlength = strlen(key)/4;
		unsigned int sum = 0;
		
		for(int i=0; i<intlength; i++)
			sum += lkey[i];
		
		// Now deal with the extra chars at the end
		int extra = strlen(key) - intlength*4;
		char temp[4];
		lkey = (unsigned int *)temp;
		lkey[0] = 0;
		
		for(int i=0; i<extra; i++)
			temp[i] = key[intlength*4+i];
			sum += lkey[0];

		return sum % HASHSIZE;
	}

	void readFile(){
    ifstream file;
    file.open ("RomeoAndJuliet.txt");
    
    if (!file.is_open()) return;

    string word;
    char* cword;
    while (file >> word){
    		// Casting a string to a write-able char*
    		cword = new char[word.length() + 1];
    		strcpy(cword, word.c_str());
    		update(cword);
    		delete [] cword;
	    }
	}

	void viewHash(){
		for(int i = 0; i < HASHSIZE; i++){
			cout << endl;
			cout << "Key: "<< data[i].key << endl;
			cout << "Value: "<<data[i].value << endl;
		}
		cout << "Size: " << c_size << endl;
	}
};

int main(){
	Hash *test = new Hash;
	test->readFile();

	// These two values hash to the same thing use for testing
	// test->update("some");
	// test->update("dare");
	// test->viewHash();

	return 0;
}

