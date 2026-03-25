#include "Bishop.h"

Bishop::Bishop(Color color) : Pieces('b', color) {}

bool Bishop::isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const  {
	// Ellenõrizzük, hogy a célmezõn saját színû bábú van-e
	if (board.getColor(board_color, to_rank, to_file) == color) {
		return false; // Nem léphet saját bábúra
	}

	if (abs(from_rank - to_rank) == abs(from_file - to_file)) {
		int rank_step = (to_rank > from_rank) ? 1 : -1;
		int file_step = (to_file > from_file) ? 1 : -1;
		for (int r = from_rank + rank_step, f = from_file + file_step; r != to_rank && f != to_file; r += rank_step, f += file_step) {
			if (!board.isEmpty(board_color, r, f)) {
				return false; // Van egy bábú az útban
			}
		}
		return true;
	}
	return false;
}