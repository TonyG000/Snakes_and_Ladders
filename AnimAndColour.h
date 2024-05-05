#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <MMSystem.h>

using namespace std;

class AnimAndColour {
public:
	const int BLUE = 1;
	const int GREEN = 2;
	const int RED = 4;
	const int WHITE = 15;
	const int YELLOW = 6;
	const int PURPLE = 5;
	const int AQUA = 3;
	const int LightPurple = 13;
	const int LightBlue = 9;
	const int LightGreen = 10;
	const int LightYellow = 14;

	void changeColour(int colour);

	void clearScreen(int characterLength);

	void showLoadingScreen();

	void showBlinkingLights();

private:

};