#include <iostream>
#include <fstream>
#include <array>
#include <map>
#define HASHSIZE 4001

using namespace std;

class Hash {
private:
	array<int, HASHSIZE> data;
	array<int, HASHSIZE> updates;
	array<int, HASHSIZE> cost;
	int size;
	int curr;

public:
	Hash(){
		for(int i = 0; i < HASHSIZE; i++){
			data[i] = 0;
			updates[i] = 0;
			cost[i] = 0;
		}
		size = 0;
		curr = -1;
	}

	int count(int index){
		return data[index];
	}

	void reset(){
		curr = -1;
	}

	void update(char *key){
		int index = sfold(key);
		data[index]++;
		size++;
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
    while (file >> word){
    		// Do stuff here
	    }
	}
};

int main(){
	Hash *test = new Hash;
	test->update("1");
	test->update("1");
	test->update("1");
	test->readFile();
	map<char*, int> mymap;

	mymap["hello"] = 1;
	cout << mymap["hello"] << endl;
	return 0;
}

