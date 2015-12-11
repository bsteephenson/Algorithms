#include <iostream>
#include <vector>

using namespace std;

#define INFINITY 999999

struct Edge {
	int weight;
	int dest;
};

struct Vertex {
	vector<Edge> adjList;
};

class Graph {
public:
	Graph(int vertex_count);
	void addEdge(int from, int to, int weight);
	void shortestPath(int source); // prints shortest paths from source to all vertices
private:
	Vertex *vertices;
	int vertex_count;
};

int main()
{
	Graph g(4);

	// fastest path from 0 to 2 should go through 1
	g.addEdge(0, 1, 4);
	g.addEdge(1, 2, 3);
	g.addEdge(0, 2, 10);
	g.addEdge(3, 0, 1);
	g.addEdge(3, 2, 12);
	g.addEdge(3, 3, 3);

	cout << "shortest path from 0" << endl;
	g.shortestPath(0);
	cout << "shortest path from 1" << endl;
	g.shortestPath(1);
	cout << "shortest path from 2" << endl;
	g.shortestPath(2);
	cout << "shortest path from 3" << endl;
	g.shortestPath(3);
}


Graph::Graph(int vertex_count)
{
	this->vertex_count = vertex_count;
	this->vertices = new Vertex[vertex_count];
}

void Graph::addEdge(int from, int to, int weight)
{
	Edge e = {weight, to};
	vertices[from].adjList.push_back(e);
}
void Graph::shortestPath(int source)
{

	// make a list of path costs and previous nodes, initialize all to 0;
	int pathCosts[this->vertex_count];
	int previous[this->vertex_count];
	for (int i = 0; i < this->vertex_count; i++) {
		pathCosts[i] = INFINITY;
		previous[i] = -1;
	}

	pathCosts[source] = 0;

	// (vertex_count - 1) times
	for (int i = 0; i < vertex_count - 1; i++) {
		// for each vertex
		for (int v = 0; v < vertex_count; v++) {
			// for each edge of that vertex
			for (auto e = vertices[v].adjList.begin(); e != vertices[v].adjList.end(); e++) {
				// relax that edge
				if (pathCosts[v] + e->weight < pathCosts[e->dest]) {
					previous[e->dest] = v;
					pathCosts[e->dest] = pathCosts[v] + e->weight;
				}
			}
		}
	}

	for (int i = 0; i < this->vertex_count; i++) {
		cout << "to vertex " <<  i << "\t prev:" << previous[i] << "  \t path-cost: " << pathCosts[i] << endl;
	}	

}
