#include <iostream>
#include <string>
#include "List.cpp"

using namespace std;

int main(){
	LinkedList<char> *list = new LinkedList<char>;
	string x = "a  9=  +  BC";
	string y = "a = 1 + 2";
	string z = "a=2^b";
	list->inputList(x);
	list->inputList(y);
	list->inputList(z);
	return 0;
}