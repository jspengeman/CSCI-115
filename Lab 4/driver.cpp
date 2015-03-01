#include <iostream>
#include "List.cpp"

using namespace std;

// This can be ran by typing: g++ driver.cpp -o driver.o then ./driver.o
int main(){
	
	// Intialize a LinkedList char type object
	LinkedList<char> *list = new LinkedList<char>;

	/*
	 * Testing the prepend and append operator then view the list
	 * This is also testing the overloaded new operator for the 
	 * link class which is within the prepend and append methods
	 */ 
	list->prepend('A');
	list->prepend('B');
	list->append('C');
	list->append('D');
	list->viewList();
	cout << endl;

	/*
	 * Testing the move to start method, the next method and 
	 * the get value method Prints out the same list as above
	 */ 
	list->moveToStart();
	cout << list->getValue() << endl;
	list->next();
	cout << list->getValue() << endl;
	list->next();
	cout << list->getValue() << endl;
	list->next();
	cout << list->getValue() << endl;
	cout << endl;

	/* 
	 * Testing the clear method and the num active and 
	 * num free methods as well as the Link the class
	 * operator over load for delete. 
	 * The number active and number free should swap
	 * because all of the nodes have been deleted
	 */  
	cout << "Active: " << list->numActive() << endl;
	cout << "Free: " << list->numFree() << endl;
	list->clear();
	cout << "Active: " << list->numActive() << endl;
	cout << "Free: " << list->numFree() << endl;
	list->viewList();
	cout << endl;

	/*
	 * Further testing on inserting and custom memory management
	 * Testing to make sure the overloaded new operator is pulling
	 * nodes from the free list which this output properly displays
	 */ 
	list->prepend('A');
	list->append('B');
	cout << "Active: " << list->numActive() << endl;
	cout << "Free: " << list->numFree() << endl;
	list->viewList();

	return 0;
}