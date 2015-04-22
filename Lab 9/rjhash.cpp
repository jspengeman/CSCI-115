#include <iostream>
#include <fstream>
#include <array>
#include <math.h> 
#define HASHSIZE 4001
#define EMPTYKEY ""

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

	void update(const char *key){
		int index = sfold(key);
		string str_key = string(key);
		// Increment the number of updates for current size
		updates[c_size]++; 

		// Check if the string is not empty
		if (data[index].key != ""){
			// Check if the string is the same
			if (data[index].key == str_key){
				data[index].value++;
			}
			// String is different, do probing
			else {
				// Doing probing here
				int curr = index;

				while(data[curr].key != EMPTYKEY && data[curr].key != str_key){
					cout << data[curr].key << endl;
					curr = ++curr % HASHSIZE; 
					cost[c_size]++;
				}

				cout << "curr: "<< curr << endl;
				data[curr].key = str_key;
				data[curr].value++;
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

	int sfold(const char* key) {
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
    while (file >> word){
    		update(word.c_str());
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
	test->viewHash();

	return 0;
}

