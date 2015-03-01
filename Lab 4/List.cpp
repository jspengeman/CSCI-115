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

	}

	void append(const E& item){

	}

	void moveToStart(){

	}

	bool next(){
		return false;
	}

	const E& getValue() const{
		return current->element;
	}

	int numActive(){
		// 
		return current->active_nodes;
	}

	int numFree(){
		return current->free_nodes;
	}
};

int main(){
	return 0;
}
