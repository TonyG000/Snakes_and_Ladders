#pragma once
#include<iostream>
#include <vector>
#include <string>
#include<sstream>
#include "Graph.h"
#include "AnimAndColour.h"

using namespace std;

const int WHITE = 15;

struct player {
	string name = "";
	int score = 0;
	bool win = 0;
	int color = WHITE;
};

class PlayerAndBoard {
public:

	int die_roll();

	void create_players(player* players, int num, AnimAndColour effects);

	void display_players(player* players, int num);

	void move_player(player* players, int turn, int roll, int& wins, Graph& g, int num, vector<player>& winners, AnimAndColour effects);

	void display_board(player* players, int num, int c1, int c2, AnimAndColour& effects);

private:
};