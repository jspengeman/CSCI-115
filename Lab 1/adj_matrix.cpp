#include <cstdlib>
#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

vector< vector<graph> > adj_matrix; //two dimensional vector to represent the adjacency matrix

void graph::print_row(int index){
  cout << index << ": ";
  int size = adj_matrix.at(index).size();

  for (int x = 0; x < size; x++){
      if (adj_matrix[index][x].edge == 1){
        cout << x << ", ";
      }
  }

  cout << endl;
}

void graph::initialize_graph(int num_of_vertices, int num_of_edges)
{
  // Declare a vector that will go inside the 2D vector
  graph empty;
  empty.edge = 0;
  vector<graph> temp;
  temp.resize(num_of_vertices);

  // Intialize that vector to all zeros
  for (int y = 0; y < num_of_vertices; y++){
    temp.at(y) = empty;
  }

  // Put those vectors inside the 2D vector
  adj_matrix.resize(num_of_vertices);
  for (int x = 0; x < num_of_vertices; x++){
    adj_matrix.at(x) = temp;   
  }

  // Insert desired number of edges
  for (int j = 0; j < num_of_edges; j++){
    cout << "Input edge in the X Y format" << endl;
    int vert1, vert2;
    cin >> vert1 >> vert2;
    insert_edge(vert1, vert2);
  }
}

void graph::insert_edge(int vertex1, int vertex2)
{
  int num_of_vertices = adj_matrix.size();
  bool isDuplicate = false;
  if (vertex2 > num_of_vertices - 1){
    cout << "Error: No number " << vertex2 << " node in graph" << endl; 
    isDuplicate = true;
  }

  if (adj_matrix[vertex1][vertex2].edge == 1 || isDuplicate == true){
    cout << "Edge is already present or vertex doesn't exist" << endl;
    int vert1, vert2;
    cout << "Enter two values that actually work: " << endl;
    cin >> vert1 >> vert2;
    insert_edge(vert1, vert2);
  }
  else {
    adj_matrix[vertex1][vertex2].edge = 1;
  }
}

void graph::delete_edge(int vertex1, int vertex2)
{
  adj_matrix.at(vertex1).at(vertex2).edge = 0;
}

void graph::list_all_edges(int num_of_vertices)
{
  // Display all edges in the form
  // vertex : edge, edge, edge
  // vertex : edge, edge, edge
  // vertex : edge, edge, edge
  for (int x = 0; x < num_of_vertices; x++){
    print_row(x);   
  }
}

void graph::list_all_neighbors(int vertex1, int num_of_vertices)
{  
  // Display all neighbors in the form
  // vertex : edge, edge, edge
  print_row(vertex1);
}

void graph::no_incoming_edges(int num_of_vertices)
{
  // Delcare an array of bools representing
  // wheter the vertex at that specific index
  // has any edges pointing to it 
  bool incoming[num_of_vertices];
  for (int i = 0; i < num_of_vertices; i++){
    incoming[i] = false;
  }

  // If an edge points to a vertex set that index
  // Equal to true, to represent it has an
  // Incoming edge
  for (int x = 0; x < num_of_vertices; x++){
    for (int y = 0; y < num_of_vertices; y++){
      if (adj_matrix[x][y].edge == 1){
        int vertex_index = y;
        incoming[vertex_index] = true;
      }
    }
  }

  // Display all vertexs with no incoming edges
  for (int j = 0; j < num_of_vertices; j++){
    if (incoming[j] == false){
      cout << "Vertex number " << j << " has no incoming edges" << endl;
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

