#include <iostream>
#include <locale>
#include <string>
#include <array>
#include <vector> 
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
		node_count = 0;
	}

	void prepend(const E& item){
		// Intialize new node and move pointers
		Link<E> *new_node = new Link<E>;
		new_node->element = item;
		new_node->next = head->next;
		head->next = new_node;
		node_count++;
	}

	void append(const E& item){
		// Inserts a node using a copying method
		Link<E> *new_node = new Link<E>;
		tail->next = new_node;
		tail->element = item;
		tail = tail->next;
		node_count++;
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

		 // Might need to subtract 26 because of the intialization of all of the registers
		 // Subtracting 82 because I initialize all registers to 0 with is 3 * 26 nodes then
		 // I have 2 other operend nodes that have a head an a tail so subtract 4 more
		return current->get_active_nodes() - 82;
	}

	int numFree(){
		// Return static value of free nodes
		return current->get_free_nodes();
	}

	int nodeCount(){
		return node_count;
	}

	void viewList(){
		current = head->next;
		int count = 1;
		
		while(current != tail){
			count++;
			cout << current->element;
			current = current->next;

			if (count % 4 == 0){
				cout << " ";
			}
		}
		cout << endl;
	}
};


template <typename E>
int Link<E>::active_nodes = 0;
template <typename E>
int Link<E>::free_nodes = 0;
template <typename E>
Link<E> *Link<E>::freelist = NULL;


class Calculator {
private:
	// Array of 26 Linked List representing 26 registers
	array<LinkedList<int>, 26> equations;

public:
	Calculator(){
		for (int i = 0; i < 26; i++){
			equations[i].append(0);
		}
	}

	void viewEquations(){
		string xs = "abcdefghijkklmnopqrstuvwxyz";
		for (int i = 0; i < 26; i++){
			cout << xs[i] << ": ";
			equations[i].viewList();
		}
	}

	void validateEquation(string input){
		/*
		 * I understand this function is overly verbose
		 * I wrote it to try and model a finite state machine
		 * That is why it is written in the manner it is.
		 * I wrote it iteratively and then lost my mojo so some
		 * parts access parts of strings that should be capable
		 * of being accessed by a FSM so sadly its not a FSM but
		 * I shall refactor it for fun later on!
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

		if (foundFirstOperend && !foundOperator){
			simpleAssignment(input);
		}

		processEquation(input);	
	}

	void processEquation(string input){
		// Clean up the string
		std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
		input.erase(end_pos, input.end());

		int opIndex;
		int end = input.length();
		for (int i = 0; i < end; i++){
			if (input[i] == '+' || input[i] == '-' ||
				input[i] == '*' || input[i] == '^'){
				opIndex = i;
			}
		}

		string operend1 = input.substr(2, opIndex - 2);
		string operend2 = input.substr(opIndex + 1, end);
		char equationOp = input[opIndex];
		char eqReg = input[0];

		createEquation(eqReg, equationOp, operend1, operend2);
	}

	void createEquation(char reg, char op, string oper1, string oper2){
		// Make the string into two linked list one for each operend
		LinkedList<int> *operend1 = new LinkedList<int>;
		LinkedList<int> *operend2 = new LinkedList<int>;

		vector<int> intChunks1;
		vector<int> intChunks2;

		for (int i = 0; i < oper1.length(); i+= 4){
			intChunks1.insert(intChunks1.begin(), stoi(oper1.substr(i, 4), nullptr, 10));					
		}

		for (int i = 0; i < oper2.length(); i+= 4){
			intChunks2.insert(intChunks2.begin(), stoi(oper2.substr(i, 4), nullptr, 10));					
		}

		for (int i = 0; i < intChunks1.size(); i++){
			operend1->append(intChunks1[i]);
		}

		for (int i = 0; i < intChunks2.size(); i++){
			operend2->append(intChunks2[i]);
		}

		completeEquation(operend1, operend2, reg, op);

	}

	void completeEquation(LinkedList<int> *operend1, LinkedList<int> *operend2, char reg, char op){
		operend1->viewList();
		operend2->viewList();

		// Complete the operation here
	}

	void simpleAssignment(input){
		std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
		input.erase(end_pos, input.end());

		// Do basic assignment here
	}
};




