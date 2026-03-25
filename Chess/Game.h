#pragma once
#include <iostream>
#include <string>
#include "Board.h"

class Game {
private:
	Board board;
	std::string player1;
	std::string player2;
	bool checkmate;
	bool draw;
public:
	Game();
	void start();
	bool input_converter(const std::string& input, int& from_rank, int& from_file, int& to_rank, int& to_file);
	void move();
	int letterToIndex(char letter);
	void setPlayerNames();
	bool getCheckMate() const;
	bool getDraw() const;
};