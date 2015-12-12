// Topological DAG sort
// Prints out a directed acyclic graph in **reverse** order

#include <iostream>
#include <stack>

using namespace std;

class Graph {
public:
	Graph(int vertices);
	void addEdge(int source, int dest);
	void printDAGSort();
private:
	void printDAGSort_rec(int markers[], int v);
	int ** make2DArray(int vertices);
	int **adjMatrix;
	int vertices;
};

int main()
{
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);

	g.addEdge(1, 3);
	g.addEdge(2, 3);

	cout << "Printing edges in reverse topologically sorted order" << endl;
	g.printDAGSort();
}

Graph::Graph(int vertices)
{
	this->vertices = vertices;
	adjMatrix = make2DArray(vertices);
}

void Graph::addEdge(int source, int dest)
{
	adjMatrix[source][dest] = 1;
}

void Graph::printDAGSort()
{
	int markers[vertices];
	for (int i = 0; i < vertices; i++) {
		markers[i] = 0;
	}
	for (int i = 0; i < vertices; i++) {
		printDAGSort_rec(markers, i);
	}

}

void Graph::printDAGSort_rec(int markers[], int v)
{
	
	if (markers[v] == 1) {
		return;
	}
	else {
		
		// say i've been here
		markers[v] = 1;

		// recurse on all my neighbors
		for (int i = 0; i < vertices; i++) {
			if (adjMatrix[v][i] != 0) {
				printDAGSort_rec(markers, i);
			}
		}

		cout << v << endl;

	}
}


int ** Graph::make2DArray(int vertices)
{
	int **array = new int * [vertices];
	for (int i = 0; i < vertices; i++) {
		array[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) {
			array[i][j] = 0;
		}
	}
	return array;
}