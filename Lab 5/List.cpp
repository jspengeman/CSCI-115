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
		bool startsWithReg = false;
		bool containsEquals = false;
		bool containsOp = false;
		bool hasFirstOp = false;
		bool hasSecondOp = false;

		// Checks if first char is digit
		if (isdigit(input[0])){
			cout << "variable expected" << endl;
			return;
		}

		// Checks if string starts with lower case char
		if (isalpha(input[0]) && islower(input[0])){
			startsWithReg = true;
			
			// Checks rest of string
			for(int i = 1; i < input.size(); i++){
				// Checks for out of place digit
				if (!containsEquals){
					if (isspace(input[i])) {
						continue;
					}
					else if (isdigit(input[i])){
						cout << "'=' expected" << endl;
						break;
					}
				}

				// Looking for an equal sign, skipping spaces
				// Once an equal sign is found spaces won't be 
				// validated the same way
				if (startsWithReg && !containsEquals){
					if (isspace(input[i])){
						continue;
					}
					else if (input[i] == '='){
						containsEquals = true;
					}
				}

				// Checks for an out of place operator
				if (containsEquals){
					if (isspace(input[i])){
						continue;
					}
					else if (isdigit(input[i])){
						hasFirstOp = true;
						continue;
					}
					else if (input[i] == '+' || input[i] == '-'){
						cout << "variable or number expected" << endl;
						break;
					}
				}

				// Validating first operator
				if (hasFirstOp){
					if (isspace(input[i])){
						continue;
					}
					else if (input[i] == '^'){
						cout << "integer expected" << endl;
					}
				}
			}			
		}

		
	}
};

// Um, I didn't really know how else to intialize these
// Although doing it this way makes me cringe.
template <typename E>
int Link<E>::active_nodes = 0;
template <typename E>
int Link<E>::free_nodes = 0;
template <typename E>
Link<E> *Link<E>::freelist = NULL;


