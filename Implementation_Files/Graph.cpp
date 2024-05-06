#include "Graph.h"

Graph::Graph() {
	// Ladders
	addEdge(1, 38, 1);
	addEdge(4, 14, 1);
	addEdge(9, 31, 1);
	addEdge(21, 42, 1);
	addEdge(28, 84, 1);
	addEdge(51, 67, 1);
	addEdge(72, 91, 1);
	addEdge(80, 99, 1);

	// Snakes
	addEdge(17, 7, 1);
	addEdge(54, 34, 1);
	addEdge(62, 19, 1);
	addEdge(64, 60, 1);
	addEdge(87, 36, 1);
	addEdge(93, 73, 1);
	addEdge(95, 75, 1);
	addEdge(98, 79, 1);
}

void Graph :: addEdge(int u, int v, int wt) {
	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt)); //reference GeeksforGeeks
}
int Graph:: getDest(int score) {
	int v, w;
	for (vector<pair<int, int>>::iterator it = adj[score].begin(); it != adj[score].end(); it++) {
		v = it->first;
		w = it->second;
		if (isLadder(score) || isSnake(score)) {
			return v; // Return the destination of the second edge
		}
	}
	return score;
}

bool Graph:: isLadder(int node) {
	// Check if the node is the starting node of a ladder
	return (node == 1 || node == 4 || node == 9 || node == 21 || node == 28 || node == 51 || node == 72 || node == 80);
}
bool Graph:: isSnake(int node) {
	return (node == 17 || node == 54 || node == 62 || node == 64 || node == 87 || node == 93 || node == 95 || node == 98);
}
