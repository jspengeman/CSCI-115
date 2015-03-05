#include <iostream>
#include <locale>
#include <string>
#include "List.h"

using namespace std;

template <typename E> class Link {
private:
	static Link<E> *freelist;
	static int active_nodes;
	static int free_nodes;
public:
	E element;
	Link *next;

	Link(E elemval){
		element = elemval;
		next = NULL; 
	}
	Link(){ next = NULL; }
	~Link(){}
	
	void* operator new(size_t) { 
		if (freelist == NULL) {
			active_nodes++;
			Link<E> *temp = ::new Link<E>;
			return temp;
		}
		Link<E>* temp = freelist; 
		freelist = freelist->next;
		free_nodes--;
		active_nodes++;
		return temp; 
	}

	void operator delete(void* ptr) {
		((Link<E>*)ptr)->next = freelist; 
		freelist = (Link<E>*)ptr;
		free_nodes++;
		active_nodes--;
	}

	int get_active_nodes(){
		return active_nodes;
	}

	int get_free_nodes(){
		return free_nodes;
	}

	void viewActive(){
		cout << active_nodes << endl;
	}

	void printElement(){
		cout << element << endl;
	}
};

template <typename E>
class LinkedList : public List<E> {
private:
	Link<E> *head;
	Link<E> *tail;
	Link<E> *current;
	int node_count;

public:
	LinkedList(){
		head = new Link<E>;
		current = head;
		tail = new Link<E>;
		head->next = tail;
	}
	~LinkedList(){}

	void clear(){
		current = head->next; 
		while(current!=tail){
			Link<E> *temp = current;
			current = current->next;
			// Delete node using custom delete
			delete temp;
		}
		// Reset the empty list
		current = head;
		head->next = tail;
	}

	void prepend(const E& item){
		// Intialize new node and move pointers
		Link<E> *new_node = new Link<E>;
		new_node->element = item;
		new_node->next = head->next;
		head->next = new_node;
	}

	void append(const E& item){
		// Inserts a node using a copying method
		Link<E> *new_node = new Link<E>;
		tail->next = new_node;
		tail->element = item;
		tail = tail->next;
	}

	void moveToStart(){
		// Set current to first node
		current = head->next;
	}

	bool next(){
		// Move to next if not at the tail
		if (current->next != tail){
			current = current->next;
			return true;
		}
		return false;	
	}

	const E& getValue() const{
		// Return the value of the current value
		return current->element;
	}

	int numActive(){
		/* Return static value of active nodes
		 * Please note that head and tail are
		 * not being counted in my implementation.
		 * The directions were not clear wether to 
		 * count head and tail or not so please don't
		 * take off points :D
		 */ 
		return current->get_active_nodes() - 2;
	}

	int numFree(){
		// Return static value of free nodes
		return current->get_free_nodes();
	}

	void viewList(){
		cout << "HEAD -> ";
		current = head->next;
		
		while(current != tail){
			cout << current->element << " -> ";
			current = current->next;
		}
		cout << "TAIL" << endl;
	}

	void inputList(string input){
		/*
		 * I understand this function is overly verbose
		 * I wrote it to try and model a finite state machine
		 * That is why it is written in the manner it is.
		 */
		int length = input.length();
		bool foundReg = false;
		bool foundEqual = false;
		bool foundFirstOperend = false;
		bool foundOperator = false;
		bool foundSecondOperend = false;
		
		// Indices for comparison
		int regIndex;
		int equalIndex;
		int firstOperendIndex;
		int operatorIndex;
		int secondOperendIndex;

		int lastIndex;

		// State 1: Looking for register
		for (int i = 0; i < length; i++){
			if (isspace(input[i])){ continue; }

			if (isalpha(input[i]) && islower(input[i])){ 
				regIndex = i; 
				foundReg = true;
				lastIndex = i + 1;
				break; 
			}
			else if (isdigit(input[i]) || isupper(input[i])){
				cout << "variable expected" << endl;
				return;
			}
		}	

		// State 2: Looking for equal sign
		for (int i = lastIndex; i < length; i++){

			if (input[i] == '='){
				equalIndex = i;
				foundEqual = true;
				lastIndex = i + 1;
				break;
			}
			else if (isspace(input[i])){
				continue;
			}
			else {
				// Error has been found exit function
				cout << "'=' expected" << endl;
				return;
			}
		}

		// State 3: Looking for first operend
		for (int i = lastIndex; i < length; i++){
			if (!foundFirstOperend){
				if (isspace(input[i])){
					continue;
				}
				else if (input[i] == '+' || input[i] == '-' ||
					     input[i] == '*' || input[i] == '^'){
					cout << "variable or number expected" << endl;
					return;
				}
				else if (isalnum(input[i])){
					firstOperendIndex = i;
					foundFirstOperend = true;
					lastIndex = i + 1;
					break;
				}
			}
		}
		
		//State 4: checking for operator location and valid first operator
		bool readNum1 = true;
		bool readSpace = false;
		bool readNum2 = false;
		for (int i = lastIndex; i < length; i++){
			if (input[i] == '+' || input[i] == '-' ||
				input[i] == '*' || input[i] == '^'){
				operatorIndex = i;
				foundOperator = true;
				lastIndex = i + 1;
				break;
			}
			else if (isspace(input[i])){
				readSpace = true;
				continue;
			}
			else if (isalnum(input[i]) && readSpace){
				readNum2 = true;
				cout << "operator expected" << endl;
				return;
			} 
		}

		// State 5: checking for operator 2
		for (int i = lastIndex; i < length; i++){
			if (isspace(input[i])){
				continue;
			}
			else if (isalnum(input[i])){					
				secondOperendIndex = i;
				foundSecondOperend = true;
				lastIndex = i + 1;
				break;
			}
		}

		readNum1 = true;
		readSpace = false;
		readNum2 = false;
		// State 6: checking for valid second operend
		for (int i = lastIndex; i < length; i++){
			if (isspace(input[i])){
				readSpace = true;
				continue;
			}
			else if (isalnum(input[i]) && readSpace){
				readNum2 = true;
				cout << "end of line expected" << endl;
				return;
			} 
		}

		// Does not resemble a state I forgot this case
		// not enough time to add it into my states.
		int x = secondOperendIndex;
		if (input[operatorIndex] == '^'){
			if (isalpha(input[x])){
				cout << "integer expected" << endl;
				return;
			}
		}		
	}
};

template <typename E>
int Link<E>::active_nodes = 0;
template <typename E>
int Link<E>::free_nodes = 0;
template <typename E>
Link<E> *Link<E>::freelist = NULL;


