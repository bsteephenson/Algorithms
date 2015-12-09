// An implentation of Dijkstras algorithm

// Depends on weights being integers 1...k with k not too large
// Uses a Radix Heap/Priority Queue to do fast insert, getMin, decreaseKey


#include <iostream>
#include <vector>

using namespace std;

#define V_MAX 3
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
	void addEdge(int from, int to, int weight);
	void shortestPath(int source); // prints shortest paths from source to all vertices
private:
	Vertex vertices[V_MAX];
};

class RadixPriorityQueue {
public:
	RadixPriorityQueue(int max);
	void insert(int id, int cost);
	void decreaseKey(int id, int from, int to); // from = previous pathCost, to = new pathCost
	int dequeueMin(); // remomves id at min and removes that id
	bool isEmpty();
private:
	vector<int> *table; // an id at index k of the table has pathCost = k
	vector<int> infinityRow; // maintain a seperate row for infinity
	int mindex; // minimum index
	int count;
};


int main() {

	Graph g;

	// fastest path from 0 to 2 should go through 1
	g.addEdge(0, 1, 4);
	g.addEdge(1, 2, 3);
	g.addEdge(0, 2, 10);
	
	cout << "shortest path from 0" << endl;
	g.shortestPath(0);
	cout << "shortest path from 1" << endl;
	g.shortestPath(1);
	cout << "shortest path from 2" << endl;
	g.shortestPath(2);

}

void Graph::addEdge(int from, int to, int weight)
{
	Edge e = {weight, to};
	vertices[from].adjList.push_back(e);
}
void Graph::shortestPath(int source)
{
	// first get a sum of all edge weights, get an upper bound on shortest path weight
	int upper_bound = 0;
	for (int i = 0; i < V_MAX; i++) {
		for (auto j = vertices[i].adjList.begin(); j != vertices[i].adjList.end(); j++) {
			upper_bound += j->weight;
		}
	}

	// make a radix heap and insert everyone.
	RadixPriorityQueue pq(upper_bound);
	for (int i = 0; i < V_MAX; i++) {
		pq.insert(i, INFINITY);
	}

	// make a list of path costs and previous nodes, initialize all to 0;
	int pathCosts[V_MAX];
	int previous[V_MAX];
	for (int i = 0; i < V_MAX; i++) {
		pathCosts[i] = INFINITY;
		previous[i] = -1;
	}

	pq.decreaseKey(source, INFINITY, 0);
	pathCosts[source] = 0;
	int v = pq.dequeueMin();

	while (!pq.isEmpty()) {

		// relax every edge of v
		for (auto e = vertices[v].adjList.begin(); e != vertices[v].adjList.end(); e++) {
			if (pathCosts[v] + e->weight < pathCosts[e->dest]) {
				pq.decreaseKey(e->dest, pathCosts[e->dest], pathCosts[v] + e->weight);
				pathCosts[e->dest] = pathCosts[v] + e->weight;
				previous[e->dest] = v;
			}
		}
		v = pq.dequeueMin();
	}

	for (int i = 0; i < V_MAX; i++) {
		cout << "to vertex " <<  i << "\t prev:" << previous[i] << "  \t path-cost: " << pathCosts[i] << endl;
	}	

}

RadixPriorityQueue::RadixPriorityQueue(int max)
{
	mindex = 0;
	table = new vector<int>[max];
	count = 0;
}
void RadixPriorityQueue::insert(int id, int cost)
{
	if (cost == INFINITY) {
		infinityRow.push_back(id);
	}
	else {
		table[cost].push_back(id);	
	}
	count++;
}
void RadixPriorityQueue::decreaseKey(int id, int from, int to)
{
	vector<int> &row = (from == INFINITY) ? infinityRow : table[from];

	int i = 0;
	while(row[i] != id) {
		i++;
	}
	
	// replace ith with last, then pop_back
	row[i] = *row.end();
	row.pop_back();

	// now insert id to another row
	table[to].push_back(id);

}

int RadixPriorityQueue::dequeueMin()
{
	
	if (count == infinityRow.size()) {
		int minVal = infinityRow.back();
		infinityRow.pop_back();
		count--;
		return minVal;
	}
	else {
		while(table[mindex].empty()) {
			mindex++;
		}
		// finally at min at this point
		int minVal = table[mindex].back();
		table[mindex].pop_back();
		count--;
		return minVal;		
	}
}

bool RadixPriorityQueue::isEmpty()
{
	return count == 0;
}