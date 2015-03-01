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

	Link(E &elemval){
		element = elemval;
		next = NULL; 
	}
	~Link(){}
	
	void* operator new(size_t) { 
		if (freelist == NULL) {
			active_nodes++;
			return ::new Link;
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

	void setFreeNodes(){
		free_nodes = 0;
	}

	void setActiveNodes(){
		free_nodes = 0;
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
		current = head->next;
	}

	bool next(){
		if (current->next != tail){
			current = current->next;
			return true;
		}
		return false;
	}

	const E& getValue() const{
		return current->element;
	}

	int numActive(){
		return current->active_nodes;
	}

	int numFree(){
		return current->free_nodes;
	}
};

int main(){
	return 0;
}
