#include <iostream>
#include <string>
#include "List.cpp"

using namespace std;

int main(){
	LinkedList<char> *list = new LinkedList<char>;
	string x = "a  9=  +  BC";
	list->inputList(x);

	return 0;
}