#include <iostream>
#include <string>
#include "List.cpp"

using namespace std;

int main(){
	LinkedList<char> *list = new LinkedList<char>;
	string x = "a9BC";
	list->inputList(x);

	return 0;
}