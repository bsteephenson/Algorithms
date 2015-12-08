// Breadth first search through a directed graph
// Prints a shortest path from A to B

#include <iostream>
#include <queue>
#include <stack>

using namespace std;


#define MAX_V 10

// nodes in a linked list of Edges
struct Edge {
	int to;
	Edge *next;
};

struct Vertex {
	int prev; // index of previous v in bfs path
	Edge *adj;
};

class Graph {
public:
	Graph();
	void insertEdge(int from, int to);
	void shortestPath(int from, int to);

private:
	Vertex vertices[MAX_V];
	void resetEdges();
};

int main()
{
	Graph *g = new Graph;
	g->insertEdge(1, 3);
	g->insertEdge(1, 4);
	g->insertEdge(1, 2);
	g->insertEdge(2, 4);
	g->insertEdge(4, 7);
	g->insertEdge(2, 5);
	g->insertEdge(5, 7);
	g->insertEdge(7, 3);
	g->shortestPath(1, 7);
}

Graph::Graph()
{
	for (int i = 0; i < MAX_V; i++) {
		vertices[i].adj = NULL;
		vertices[i].prev = -1;
	}
}

void Graph::insertEdge(int from, int to)
{
	Vertex v = vertices[from];
	Edge *edge = new Edge;
	edge->to = to;
	
	// insert edge as head of v's linked list
	edge->next = v.adj;
	v.adj = edge;
	
	vertices[from] = v;

}

void Graph::shortestPath(int from, int to) {
	queue<int> q;
	q.push(from);

	vertices[from].prev = -2; // prevent cycling

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		// push each of that vertex's neighbors
		Edge *e = vertices[v].adj;
		while (e != NULL) {
			if (vertices[e->to].prev == -1) {
				vertices[e->to].prev = v;
				q.push(e->to);
			}
			e = e->next;
		}
	}

	// walk backwards from destination and push path onto stack

	stack<int> path;
	int v = to;
	while (vertices[v].prev >= 0) {
		path.push(v);
		v = vertices[v].prev;
	}

	path.push(from);

	while (!path.empty()) {
		cout << path.top() << endl;
		path.pop();
	}

	this->resetEdges();

}

void Graph::resetEdges()
{
	for (int i = 0; i < MAX_V; i++) {
		vertices[i].prev = -1;
	}
}

