#include <iostream>
#include <string>
#include "List.cpp"

using namespace std;

int main(){
	LinkedList<char> *list = new LinkedList<char>;
	string a = "9ab";
	string b = "a9b"; 
	string c = "a=+b"; 
	string d = "a=123 456 + 12";
	string e = "a=2  ^  b";
	string f = "a= 12 + 1 B";
	cout << "1: ";
	list->inputList(a);
	cout << "2: ";
	list->inputList(b);
	cout << "3: ";
	list->inputList(c);
	cout << "4: ";
	list->inputList(d);
	cout << "5: ";
	list->inputList(e);
	cout << "6: ";
	list->inputList(f);
	return 0;
}