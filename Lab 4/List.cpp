#include <iostream>
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
	~Link(){}
	
	void* operator new(size_t) { 
		if (freelist == NULL) {
			active_nodes++;
			return ::new Link<E>;
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
	}

	void viewActive(){
		cout << active_nodes << endl;
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
		for(current = head->next; current!=tail; current = current->next){
			Link<E> *temp = current;
			delete temp;
		}
	}

	void prepend(const E& item){
		// Intialize new node and move pointers
		Link<E> new_node = new Link<E>;
		new_node->element = item;
		new_node->next = head->next;
		head->next = new_node;
	}

	void append(const E& item){
		// Inserts a node using a copying method
		Link<E> new_node = new Link<E>;
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
		// Return static value of active nodes
		return current->active_nodes;
	}

	int numFree(){
		// Return static value of free nodes
		return current->free_nodes;
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

int main(){
	Link<char> *test = new Link<char>('A');
	test->viewActive();
	return 0;
}
