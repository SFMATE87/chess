#include "Queen.h"

Queen::Queen(Color color) : Pieces('q', color) {}

bool Queen::isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const
{
	// mozgási változás (delta)
    int rank_delta = to_rank - from_rank;
    int file_delta = to_file - from_file;

	// Lépés ellenõrzése fuggõleges, vízszintes és keresztben
    if (rank_delta == 0 || file_delta == 0 || abs(rank_delta) == abs(file_delta)) {
        //A lépés irányának meghatározása
        int rank_step = (rank_delta == 0) ? 0 : (rank_delta > 0 ? 1 : -1);
        int file_step = (file_delta == 0) ? 0 : (file_delta > 0 ? 1 : -1);

        //Van e bábu az utban
        int current_rank = from_rank + rank_step;
        int current_file = from_file + file_step;
        while (current_rank != to_rank || current_file != to_file) {
            if (!board.isEmpty(board_color, current_rank, current_file)) {
                return false;
            }
            current_rank += rank_step;
            current_file += file_step;
        }

		// Ellenõrizzük, hogy a cél mezõ üres-e vagy az ellenfél bábúja van rajta
        Color destination_color = board.getColor(board_color, to_rank, to_file);
        if (destination_color == NONE || destination_color != board.getColor(board_color, from_rank, from_file)) {
            return true; // Valid move
        }
    }
    return false;
}
