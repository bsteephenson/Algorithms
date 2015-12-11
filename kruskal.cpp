// Find the Minimum Spanning Tree of a weighted undirected graph using Kruskal's algorithm

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Edge {
	int weight;
	int start;
	int dest;
};

class Graph {
public:
	void addEdge(int from, int to, int weight);
	void minimumSpanningTree(); // prints all the edges in a minimum spanning tree
private:
	vector<Edge> edges;
	void sortEdges(); // sort the edges by weight
};

// Unions - used to figure out which nodes are connected and to connect nodes
class Unions {
public:
	bool areConnected(int v1, int v2);
	void connect(int v1, int v2);
private:
	vector< set<int> > sets;
	int find(int v); // return -1 or the index of the set v lives in
};


int main()
{
	Graph g;

	// fastest path from 0 to 2 should go through 1
	g.addEdge(0, 1, 4);
	g.addEdge(1, 2, 3);
	g.addEdge(0, 2, 10);
	g.addEdge(3, 0, 1);
	g.addEdge(3, 2, 12);
	g.addEdge(3, 3, 3);

	cout << "Edges in MST" << endl;
	g.minimumSpanningTree();

}



void Graph::addEdge(int from, int to, int weight)
{
	Edge e = {weight, from, to};
	this->edges.push_back(e);
}

void Graph::minimumSpanningTree()
{
	this->sortEdges();
	Unions u;
	vector<Edge> mst;
	for (auto e = edges.begin(); e != edges.end(); e++) {
		if (!u.areConnected(e->start, e->dest)) {
			mst.push_back(*e);
			u.connect(e->start, e->dest);
		}
	}

	for (auto e = mst.begin(); e != mst.end(); e++) {
		cout <<"from "<<  e->start << " to " << e->dest << " with weight " << e->weight << endl;
	}
}

void Graph::sortEdges()
{
	// super simple insertion sort
	for (int i = 1; i < edges.size(); i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (edges[j].weight > edges[j + 1].weight) {
				Edge temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
			else {
				break;
			}
		}
	}
}


bool Unions::areConnected(int v1, int v2)
{
	int v1_index = find(v1);
	int v2_index = find(v2);
	if (v1_index == -1 || v2_index == -1) {
		return false;
	}
	else {
		return v1_index == v2_index;
	}
}
void Unions::connect(int v1, int v2)
{
	int v1_index = find(v1);
	int v2_index = find(v2);
	if (v1_index == -1 && v2_index == -1) {
		set<int> s;
		s.insert(v1);
		s.insert(v2);
		sets.push_back(s);
	}
	else if (v1_index == -1) {
		sets[v2_index].insert(v1);
	}
	else if (v2_index == -1) {
		sets[v1_index].insert(v2);
	}
	else {
		set<int> v2_set = sets[v2_index];
		sets[v1_index].insert(v2_set.begin(), v2_set.end());
		// remove v2_set from array
		// .. or be lazy and just clear it...
		sets[v2_index].clear();
	}
}

int Unions::find(int v)
{
	for (int i = 0; i < sets.size(); i++) {
		if (sets[i].find(v) != sets[i].end()) {
			return i;
		}		
	}
	return -1;
}

