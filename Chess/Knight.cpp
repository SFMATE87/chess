#include "Knight.h"

Knight::Knight(Color color) : Pieces('n', color) {}

bool Knight::isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const
{
	// L-alakú lépés: 2 mezõ vízszintesen és 1 mezõ függõlegesen, vagy fordítva
	if ((abs(from_rank - to_rank) == 2 && abs(from_file - to_file) == 1) ||
		(abs(from_rank - to_rank) == 1 && abs(from_file - to_file) == 2)) {
		// Ellenõrizzük, hogy a célmezõ üres-e vagy az ellenfél bábúja van rajta
		if (board.isEmpty(board_color, to_rank, to_file) || board.getColor(board_color, to_rank, to_file) != color) {
			return true;
		}
	}
	return false;
}
