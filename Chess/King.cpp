#include "King.h"

King::King(Color color) : Pieces('k', color) {}

bool King::isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const
{
	if (abs(from_rank - to_rank) <= 1 && abs(from_file - to_file) <= 1) {
		if (board.isEmpty(board_color, to_rank, to_file) || board.getColor(board_color, to_rank, to_file) != color) {
			return true;
		}
	}
	return false;
}