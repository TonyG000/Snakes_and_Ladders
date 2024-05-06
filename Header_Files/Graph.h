#pragma once
#include <cstdlib>
#include<vector>
#include <iterator>
#include <iostream>
using namespace std;

class Graph {
	vector<pair<int, int>> adj[101];
public:
	
	Graph();

	void addEdge(int u, int v, int wt);
	int getDest(int score);

	bool isLadder(int node);
	bool isSnake(int node);

private:
};
