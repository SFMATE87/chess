#pragma once
#include "Pieces.h"
#include "Board.h"
#include <iostream>

class Pawn : public Pieces {
public:
	Pawn(Color color);
	bool isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const override;
};