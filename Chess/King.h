#pragma once
#include "Pieces.h"
#include <iostream>

class King : public Pieces {
public:
	King(Color color);
	bool isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const override;
};