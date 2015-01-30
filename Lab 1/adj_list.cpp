#include <cstdlib>
#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

vector<graph*> adj_list; // one dimensional vector; each position in the vector stores a pointer to the head of a linked list

void graph::print_row(int index){
    cout << index << ": ";
    for (graph *curr = adj_list.at(index)->head; curr != NULL; curr = curr->next){
        cout << curr->edge << ", ";
    }
    cout << endl;
}

void graph::initialize_graph(int num_of_vertices, int num_of_edges){
    // Intialize graph of head ptr nodes of graph 
    for (int i = 0; i < num_of_vertices; i++){ 
        graph *root = new graph;
        root->head = NULL;
        adj_list.insert(adj_list.begin(), root);
    }

    // Intialize edges
    for (int j = 0; j < num_of_edges; j++){
        cout << "Input edge in the X Y format" << endl;
        int vert1, vert2;
        cin >> vert1 >> vert2;
        insert_edge(vert1, vert2);
    }
}

void graph::insert_edge(int vertex1, int vertex2){
    graph *new_graph = new graph;
    new_graph->edge = vertex2;
    new_graph->prev = NULL;
    new_graph->next = NULL;
    graph *root = adj_list.at(vertex1);

    int num_of_vertices = adj_list.size();
    bool isPresent = false;

    // Basic error checking
    if (vertex2 > num_of_vertices - 1){
        cout << "Error: No number " << vertex2 << "node in graph" << endl; 
        return;
    }


    for (graph *curr = adj_list.at(vertex1)->head; curr != NULL; curr = curr->next){
        if (curr->edge == vertex2){
            isPresent = true;
            break;
        }
    }

    if (isPresent == false){
        if (root->head == NULL){
            root->head = new_graph;
        }
        else {
            root->head->prev = new_graph;
            new_graph->next = root->head;
            root->head = new_graph;
        }
    }

    // Restart the function so that it inserts the correct number of edges
    if (isPresent == true){
        int vert1, vert2;
        cout << "Enter two values that actually work: " << endl;
        cin >> vert1 >> vert2;
        insert_edge(vert1, vert2);
    }
}

void graph::delete_edge(int vertex1, int vertex2)
{  
    // This is the worst spaghetti code I have written
    // God bless the poor soul who reads this. RIP your brain.
    // I will try my best to outline all of the cases that are covered

    // Basic error checking taking place
    if (vertex1 > adj_list.size()){
        cout << "No number " << vertex1 << " vertex" << endl;
        return;
    }

    graph *root = adj_list.at(vertex1);

    // No nodes to delete
    if (root->head == NULL){
        cout << "That vertex has no edges" << endl;
    }
    else if (root->head != NULL){
        // Target is head node;
        cout << root->head->edge << endl;
        if (root->head->edge == vertex2){
            graph *temp = root->head;
            // Target is head node and singleton node
            if (root->head->next != NULL){
                graph *new_head = root->head->next;
                root->head = new_head;
                new_head->prev = NULL;
            }
            else {
                root->head = NULL;
            }
            delete temp;

            // Finish the function here so it doesn't run the for loop
            return;
        }

        // Handles deleting any node that is not the first node of the linked list
        bool isDeleted = false;
        for (graph *curr = adj_list.at(vertex1)->head; curr != NULL; curr = curr->next){
            graph *temp = curr;

            // Target is tail node
            if (curr->edge == vertex2 && curr->next == NULL){
                graph *new_last = curr->prev;
                curr->prev = NULL;
                new_last->next = NULL;
                isDeleted = true;
                delete temp;
                break;
            }
            // Target is middle node
            else if (curr->edge == vertex2){
                graph *prior_node = curr->prev;
                graph *next_node = curr->next;
                prior_node->next = next_node;
                next_node->prev = prior_node;
                isDeleted = true;
                delete temp;
                break;
            }
        }
        if (isDeleted == true) {
            cout << "Succesfully deleted" << "(" << vertex1 << ", " << vertex2 << ")" << endl;
        }
        else {
            cout << "Deletion of " << "(" << vertex1 << ", " << vertex2 << ")" << " failed"<< endl;
            cout << "Error" <<vertex2 << " is out of bounds" << endl;
        }
    }
}

void graph::list_all_edges(int num_of_vertices)
{    
    for (int x = 0; x < num_of_vertices; x++){
        print_row(x);
    }  
}

void graph::list_all_neighbors(int vertex1, int num_of_vertices)
{  
    // I useded print row to display a row so this will 
    // display all neighbors of a specific vertex just dandy
    print_row(vertex1);
}

void graph::no_incoming_edges(int num_of_vertices)
{ 
    // Intializes the array that will represent 
    // whether the value at that specific index
    // of the array has incoming edges or not
    bool incoming[num_of_vertices];
    for (int y = 0; y < num_of_vertices; y++){
        incoming[y] = false;
    }

    // For every edge that exists flag the vertex
    // It points to in the array index as true
    for (int j = 0; j < adj_list.size(); j++){
        for (graph *curr = adj_list.at(j)->head; curr != NULL; curr = curr->next){ 
            incoming[curr->edge] = true;
        }   
    }

    // For every bool in the array that is false
    // Display that it has no edges pointing to it
    for (int x = 0; x < num_of_vertices; x++){
        if (incoming[x] == false){
            cout << "Vertex number " << x << " has no incoming edges" << endl;
        }
    }

}


int main(){
    int num_of_vertices, num_of_edges, vertex1, vertex2, function;
    graph graph_obj;
    
    
    while(1){
        
        cout<<"1 - initialize graph" <<endl;
        cout<<"2 - insert an edge to the graph" <<endl;
        cout<<"3 - delete an edge from the graph" <<endl;
        cout<<"4 - list all edges in the graph" <<endl;
        cout<<"5 - list all of the neighbors for a particular vertex" << endl;
        cout<<"6 - list all of the vertices with no incoming edges" << endl << endl;
        
        cout<<"Choose a function (1 - 6): ";
        cin>>function;
        cout<<endl<<endl;
        
        switch(function){
          case 1: 
                cout<<"Enter the number of vertices in the graph: ";
                cin>>num_of_vertices;
                cout<<endl<<"Enter the number of edges in the graph: ";
                cin>>num_of_edges;
                cout<<endl<<endl;
                graph_obj.initialize_graph(num_of_vertices, num_of_edges);
                break;
         
         case 2: 
                cout<<"To enter an edge X -> Y (an edge from node X to node Y), use the following format: X Y (the names of the two vertices separated by a single space)" << endl;
                cout<<"Enter the edge to insert into the graph: ";
                cin>>vertex1>>vertex2;
                cout<<endl<<endl;
                graph_obj.insert_edge(vertex1, vertex2);         
                break;
         
         case 3: 
                cout<<"To enter an edge X -> Y (an edge from node X to node Y), use the following format: X Y (the names of the two vertices separated by a single space)" << endl;
                cout<<"Enter the edge to delete from the graph: ";
                cin>>vertex1>>vertex2;
                cout<<endl<<endl;
                graph_obj.delete_edge(vertex1, vertex2);         
                break;
       
         case 4:
                graph_obj.list_all_edges(num_of_vertices);
                break;
         
         case 5:   
                cout<<"Enter the vertex to list all of the neighbors for: ";
                cin>>vertex1;
                cout<<endl<<endl;
                graph_obj.list_all_neighbors(vertex1, num_of_vertices);
                break;
                
         case 6:
               graph_obj.no_incoming_edges(num_of_vertices);
        } //end switch
        cout<<endl<<endl<<endl;
    }  //end while   
    return 0;
}
