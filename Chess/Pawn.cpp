#include "Pawn.h"
#include "Board.h"
#include "Game.h"

Pawn::Pawn(Color color) : Pieces('p', color) {}

bool Pawn::isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const
{
	if (color == WHITE) {
		if (from_rank == 1 && to_rank == 3 && from_file == to_file && board.isEmpty(board_color, to_rank, to_file)) {
			return true; // dupla lepes
		}
		else if (from_rank + 1 == to_rank && from_file == to_file && board.isEmpty(board_color, to_rank, to_file)) {
			return true; // szimpla lepes
		}
		else if (from_rank + 1 == to_rank && abs(from_file - to_file) == 1
			&& board.getColor(board_color, to_rank, to_file) == BLACK) {
			return true; // leüti
		}
	}
	else if (color == BLACK) {
		if (from_rank == 6 && to_rank == 4 && from_file == to_file && board.isEmpty(board_color, to_rank, to_file)) {
			return true; // dupla lepes
		}
		else if (from_rank - 1 == to_rank && from_file == to_file && board.isEmpty(board_color, to_rank, to_file)) {
			return true; // szimpla lepes
		}
		else if (from_rank - 1 == to_rank && abs(from_file - to_file) == 1
			&& board.getColor(board_color, to_rank, to_file) == WHITE) {
			return true; // leüti
		}
	}
	return false;
}