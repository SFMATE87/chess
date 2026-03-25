#include "Rook.h"

Rook::Rook(Color color) : Pieces('r', color) {}

bool Rook::isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const
{
	// Ellenõrizzük, hogy a célmezõn saját színû bábú van-e
	if (board.getColor(board_color, to_rank, to_file) == color) {
		return false; // Nem léphet saját bábúra
	}

	if (from_rank == to_rank) {
		int step = (to_file > from_file) ? 1 : -1;
		for (int f = from_file + step; f != to_file; f += step) {
			if (!board.isEmpty(board_color, from_rank, f)) {
				return false; // Van egy bábú az útban
			}
		}
		return true;
	}
	else if (from_file == to_file) {
		int step = (to_rank > from_rank) ? 1 : -1;
		for (int r = from_rank + step; r != to_rank; r += step) {
			if (!board.isEmpty(board_color, r, from_file)) {
				return false; // Van egy bábú az útban
			}
		}
		return true;
	}
	return false;
}
