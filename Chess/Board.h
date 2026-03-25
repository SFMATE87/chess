#pragma once
#include <iostream>
#include <string>

enum Color { WHITE, BLACK, NONE };
enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, EMPTY };

class Board {
private:
	int piece[64];
	int color[64];
	Color turncolor; //Beáálítás
public:
	Board(bool);
	Board();
	const int* getPieceArray() const;
	const int* getColorArray() const;
	void printBoard();
	std::string pieceToSymbol(Color c, Piece p);
	void promotion(int from_rank, int to_rank, int to_file);
	Color getTurnColor() const;
	void switchTurnColor();
	void movePiece(int from_rank, int from_file, int to_rank, int to_file);
	void moveTempPiece(int board_piece[64], int board_color[64], int from_rank, int from_file, int to_rank, int to_file) const;
	Color getColor(const int board_color[64], int rank, int file) const;
	bool isEmpty(const int board_color[64], int rank, int file) const; 
	bool isValidMove(const int board_piece[64], const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, Color piece_color) const;
	bool isPieceUnderAttack(const int board_piece[64], const int board_color[64], int piece_type, Color piece_color) const;
	bool isKingInCheck(const int board_piece[64], const int board_color[64], Color king_color) const;
	bool isPieceAttackCanBeBlocked(const int board_piece[64], const int board_color[64], int piece_type, Color piece_color) const;
	bool canPieceBeDefended(const int board_piece[64], const int board_color[64], int piece_type, Color piece_color) const;
	bool isCheckmate(Color king_color) const;
	void copyBoardState(int board_piece[64], int board_color[64]) const;
	bool wouldMoveCasuseCheck(int from_rank, int from_file, int to_rank, int to_file, Color king_color) const;
	bool KingDraw(const int board_piece[64], const int board_color[64]) const;
};