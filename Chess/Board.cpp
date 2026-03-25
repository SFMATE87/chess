#include <iostream>
#include <Windows.h>
#include <string>
#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"

Board::Board(bool pt = true) : piece{EMPTY}, color{NONE}, turncolor(WHITE)
{

   // Inicializálás
   for (int i = 0; i < 64; i++) {
       piece[i] = EMPTY;
   }

   // Inicializálás
   for (int i = 0; i < 64; i++) {
       color[i] = NONE;
   }

   // Alap kiindulás beállítása
   int tempPiece[64] = {
       ROOK,  KNIGHT, BISHOP, QUEEN, KING,  BISHOP, KNIGHT, ROOK,
       PAWN,  PAWN,   PAWN,   PAWN,  PAWN,  PAWN,   PAWN,   PAWN,
       EMPTY, EMPTY,  EMPTY,  EMPTY, EMPTY, EMPTY,  EMPTY,  EMPTY,
       EMPTY, EMPTY,  EMPTY,  EMPTY, EMPTY, EMPTY,  EMPTY,  EMPTY,
       EMPTY, EMPTY,  EMPTY,  EMPTY, EMPTY, EMPTY,  EMPTY,  EMPTY,
       EMPTY, EMPTY,  EMPTY,  EMPTY, EMPTY, EMPTY,  EMPTY,  EMPTY,
       PAWN,  PAWN,   PAWN,   PAWN,  PAWN,  PAWN,   PAWN,   PAWN,
       ROOK,  KNIGHT, BISHOP, QUEEN, KING,  BISHOP, KNIGHT, ROOK
   };

   int tempColor[64] = {
       BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
       NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,
       NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,
       NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,
       NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,  NONE,
       WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
       WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
   };

   //Átmáolás
   for (int i = 0; i < 64; i++) {
	   piece[i] = tempPiece[i];
	   color[i] = tempColor[i];
   }
}

Board::Board() : piece{ EMPTY }, color{ NONE }, turncolor(WHITE) {}

const int* Board::getPieceArray() const
{
    return piece;
}

const int* Board::getColorArray() const
{
    return color;
}


void Board::printBoard()
{
    system("cls"); // Clear-eli a konzolt

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Define colors (background + text)
    const int WHITE_SQUARE = 112;  // Fehér háttér (7) + fekete szöveg (0) → 7*16 + 0 = 112
    const int BLACK_SQUARE = 128;  // Fekete háttér (8) + fehér szöveg (7) → 8*16 + 7 = 135 
    const int WHITE_PIECE = 15;    // Fehér szöveg (15) sima háttérrel
    const int BLACK_PIECE = 0;     // Fekete szöveg (0) sima háttérrel
    const int DEFAULT_COLOR = 7;   // Alap konzol szín

    std::string divider = "  +---+---+---+---+---+---+---+---+";
    std::cout << divider << std::endl;

    for (int rank = 8; rank > 0; rank--) {
        std::cout << rank << " |";
        for (int file = 0; file < 8; file++) {
            int index = (8 - rank) * 8 + file;

            // Ellenőrizzük hogy a négyzet az fekete vagy fehér legyen
            bool isWhiteSquare = (rank + file) % 2 == 0;

            // Háttér szín
            SetConsoleTextAttribute(hConsole, isWhiteSquare ? WHITE_SQUARE : BLACK_SQUARE);

            // bábu megjelenitése, helyes háttérrel
            if (color[index] == WHITE) {
                SetConsoleTextAttribute(hConsole, isWhiteSquare ? (112 + 15) : (128 + 15)); // White piece
            }
            else {
                SetConsoleTextAttribute(hConsole, isWhiteSquare ? (112 + 0) : (128 + 0)); // Black piece
            }

            std::cout << " " << pieceToSymbol((Color)color[index], (Piece)piece[index]) << " ";

            // Reseteljük a színt "|" divider
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            std::cout << "|";
        }
        std::cout << std::endl;
        std::cout << divider << std::endl;
    }
    std::cout << "    a   b   c   d   e   f   g   h " << std::endl;

    // Visszaállítjuk alapra
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}
std::string Board::pieceToSymbol(Color c, Piece p) {
    if (p == EMPTY) return " ";
	if (c == EMPTY) return " ";

    switch (p) {
    case PAWN:   return (c == WHITE) ? "p" : "P";
    case KNIGHT: return (c == WHITE) ? "n" : "N";
    case BISHOP: return (c == WHITE) ? "b" : "B";
    case ROOK:   return (c == WHITE) ? "r" : "R";
    case QUEEN:  return (c == WHITE) ? "q" : "Q";
    case KING:   return (c == WHITE) ? "k" : "K";
	default: return "?"; // Ismeretlen bábú
    }
}

void Board::promotion(int from_rank, int to_rank, int to_file)
{
    for (int i = 0; i < 64; i++) {
		int to_index = (7 - to_rank) * 8 + to_file;
        if (piece[i] == PAWN && (to_rank == 7 || to_rank == 0) && (to_index == i)) { // csak akkor promotaljuk ha megegyezik a keresett babuval
            std::cout << "Valassz egy babut (r: rook, q: queen, b: bishop, kinght: n): ";
            char choice;
            std::cin >> choice;
            switch (choice) {
            case 'r':
                piece[i] = ROOK;
                break;
            case 'q':
                piece[i] = QUEEN;
                break;
            case 'b':
                piece[i] = BISHOP;
                break;
            case 'n':
                piece[i] = KNIGHT;
                break;
            default:
                std::cout << "Érvénytelen választás!" << std::endl;
            }
        }
    }
}

Color Board::getTurnColor() const
 {
	return turncolor;
}

void Board::switchTurnColor()
{
	if (turncolor == WHITE) {
		turncolor = BLACK;
	}
	else {
		turncolor = WHITE;
	}
}

void Board::movePiece(int from_rank, int from_file, int to_rank, int to_file)
{
    int from_index = (7 - from_rank) * 8 + from_file;
    int to_index = (7 - to_rank) * 8 + to_file;

    piece[to_index] = piece[from_index];
    color[to_index] = color[from_index];
    piece[from_index] = EMPTY;
    color[from_index] = NONE;
}

void Board::moveTempPiece(int board_piece[64], int board_color[64], int from_rank, int from_file, int to_rank, int to_file) const
{
	int from_index = (7 - from_rank) * 8 + from_file;
	int to_index = (7 - to_rank) * 8 + to_file;

	board_piece[to_index] = board_piece[from_index];
	board_color[to_index] = board_color[from_index];
	board_piece[from_index] = EMPTY;
	board_color[from_index] = NONE;
}

Color Board::getColor(const int board_color[64], int rank, int file) const
{
    return (Color)board_color[(7-rank) * 8 + file];
}

bool Board::isEmpty(const int board_color[64], int rank, int file) const
{
    int index = (7-rank) * 8 + file;
    return board_color[index] == NONE;
}

bool Board::isValidMove(const int board_piece[64], const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, Color piece_color) const
{
	int from_index = (7-from_rank) * 8 + from_file;
	int to_index = (7-to_rank) * 8 + to_file;

    //Van-e valami ott
    if (board_piece[from_index] == EMPTY) {
		return false;
    }

    //Az adott játékoshoz tartozik e a bábu
    if (board_color[from_index] != piece_color) {
		return false;
    }

	//A cél mező üres-e
    if (board_color[to_index] == piece_color) {
		return false;
    }

    switch (board_piece[from_index]) {
    case PAWN: {
        Pawn pawn((Color)board_color[from_index]);
        return pawn.isValidMove(board_color, from_rank, from_file, to_rank, to_file, *this);
    }
    case KNIGHT: {
        Knight knight((Color)board_color[from_index]);
        return knight.isValidMove(board_color, from_rank, from_file, to_rank, to_file, *this);
    }
    case KING: {
        King king((Color)board_color[from_index]);
        return king.isValidMove(board_color, from_rank, from_file, to_rank, to_file, *this);
    }
    case BISHOP: {
        Bishop bishop((Color)board_color[from_index]);
        return bishop.isValidMove(board_color, from_rank, from_file, to_rank, to_file, *this);
    }
	case ROOK: {
		Rook rook((Color)board_color[from_index]);
		return rook.isValidMove(board_color, from_rank, from_file, to_rank, to_file, *this);
	}
	case QUEEN: {
		Queen queen((Color)board_color[from_index]);
   		return queen.isValidMove(board_color, from_rank, from_file, to_rank, to_file, *this);
	}
    
		default:
			std::cout << "Ismeretlen bábu!" << std::endl;
			return false;
     }
}

bool Board::isPieceUnderAttack(const int board_piece[64], const int board_color[64], int piece_type, Color piece_color) const
{
    int piece_index = -1;

    // Keressuk meg a babu poziciojat
    for (int i = 0; i < 64; i++) {
        if (board_piece[i] == piece_type && board_color[i] == piece_color) {
            piece_index = i;
            break;
        }
    }
    if (piece_index == -1) { //A babut nem találtuk meg
        return false; 
    }

    // Ellenőrizzük, hogy az ellenfél bábúja le tudja e ütni a ezt a babut
    for (int i = 0; i < 64; i++) {
        if (board_color[i] != piece_color && board_piece[i] != EMPTY) {
            int from_rank = 7 - (i / 8);
            int from_file = i % 8;
            int to_rank = 7 - (piece_index / 8);
            int to_file = piece_index % 8;

            Color inverse_color = (piece_color == WHITE) ? BLACK : WHITE;
            if (isValidMove(board_piece, board_color, from_rank, from_file, to_rank, to_file, inverse_color)) {
                return true; // A babu tamadas allatt van
            }
        }
    }

    return false; // A babu nincs tamadas allatt
}

bool Board::isKingInCheck(const int board_piece[64], const int board_color[64], Color king_color) const
{
	return isPieceUnderAttack(board_piece, board_color, KING, king_color);

}

bool Board::isPieceAttackCanBeBlocked(const int board_piece[64], const int board_color[64], int piece_type, Color piece_color) const
{
    int piece_index = -1;

    //Megkeressuk a babu poziciojat
    for (int i = 0; i < 64; i++) {
        if (board_piece[i] == piece_type && board_color[i] == piece_color) {
            piece_index = i;
            break;
        }
    }

    if (piece_index == -1) {
		return false; // Nem talalhato a babu
    }

    // a tamado babu pozicioja
    int attacker_index = -1;
    for (int i = 0; i < 64; i++) {
        if (board_color[i] != piece_color && board_piece[i] != EMPTY) {
            int from_rank = 7 - (i / 8);
            int from_file = i % 8;
            int to_rank = 7 - (piece_index / 8);
            int to_file = piece_index % 8;

            Color inverse_color = (piece_color == WHITE) ? BLACK : WHITE;

            if (isValidMove(board_piece, board_color, from_rank, from_file, to_rank, to_file, inverse_color)) {
                attacker_index = i;
                break;
            }
        }
    }

    if (attacker_index == -1) {
        return false; // Nem talalhato tamado babu
    }

    int attacker_rank = 7 - (attacker_index / 8);
    int attacker_file = attacker_index % 8;

    // Megnezzuk hogy van e olyan babu ami ki tudja blokkolni a tamadast
    for (int i = 0; i < 64; i++) {
        if (board_color[i] == piece_color && board_piece[i] != EMPTY) {
            int from_rank = 7 - (i / 8);
            int from_file = i % 8;

			// minden lehetseges lepest megnezzunk
            for (int to_rank = 0; to_rank < 8; to_rank++) {
                for (int to_file = 0; to_file < 8; to_file++) {
                    if (isValidMove(board_piece, board_color, from_rank, from_file, to_rank, to_file, piece_color)) {

                        int temp_piece[64];
                        int temp_color[64];

                        copyBoardState(temp_piece, temp_color);
                        moveTempPiece(temp_piece, temp_color, from_rank, from_file, to_rank, to_file);

                        // megnezzuk hogy valoban blokkolja e a tamadast
                        if (!isKingInCheck(temp_piece, temp_color, piece_color)) {
                            return true; // lehet blokkolni
                        }
                    }
                }
            }
        }
    }

    return false; // nem lehet blokkolni
}

bool Board::canPieceBeDefended(const int board_piece[64], const int board_color[64], int piece_type, Color piece_color) const
{
    int piece_index = -1;

	// Keressuk meg a babu poziciojat
    for (int i = 0; i < 64; i++) {
        if (board_piece[i] == piece_type && board_color[i] == piece_color) {
            piece_index = i;
            break;
        }
    }

    if (piece_index == -1) {
		return false; // a babu nem talalhato
    }

	int piece_rank = 7 - (piece_index / 8);
    int piece_file = piece_index % 8;

    //Ellenőrizzük hogy a babu el tud e menelkulni
    for (int dr = -1; dr <= 1; dr++) {
        for (int df = -1; df <= 1; df++) {
            if (dr == 0 && df == 0) continue; // ugyanoda ne lépjen

            int new_rank = piece_rank + dr;
            int new_file = piece_file + df;


            if (new_rank >= 0 && new_rank < 8 && new_file >= 0 && new_file < 8) { //Csak akkor nezzuk meg ha bent van a palyan
                if (isValidMove(board_piece, board_color, piece_rank, piece_file, new_rank, new_file, piece_color)) {
                    int temp_piece[64] = { EMPTY };
                    int temp_color[64] = { NONE };
                    copyBoardState(temp_piece, temp_color);
                    moveTempPiece(temp_piece, temp_color, piece_rank, piece_file, new_rank, new_file);

                    if (!isPieceUnderAttack(temp_piece, temp_color, piece_type, piece_color)) {
                        return true; // A babu el tud menekulni
                    }
                }
            }
        }
    }
	return false; // A babu nem tud elmenekulni
}

bool Board::isCheckmate(Color king_color) const
{
	if (!isKingInCheck(piece, color, king_color)) {
		return false; // Ha a kiraly nincs sakkban, akkor nem matt
	}

    if (isPieceAttackCanBeBlocked(piece, color, KING, king_color)) {
		return false; // Ha a tamadast blokkolni lehet, akkor nem matt
    }

	return !canPieceBeDefended(piece, color, KING, king_color);
}

void Board::copyBoardState(int board_piece[64], int board_color[64]) const
{
	for (int i = 0; i < 64; i++) {
		board_piece[i] = piece[i];
		board_color[i] = color[i];
	}
}

bool Board::wouldMoveCasuseCheck(int from_rank, int from_file, int to_rank, int to_file, Color king_color) const
{
    int temp_piece[64];
    int temp_color[64];

    copyBoardState(temp_piece, temp_color);

    moveTempPiece(temp_piece, temp_color, from_rank, from_file, to_rank, to_file);

	return isKingInCheck(temp_piece, temp_color, king_color);

}

//azt bezzuk hogy ha csak a ketto kiraly maradt akkor dontetlen
bool Board::KingDraw(const int board_piece[64], const int board_color[64]) const
{
    int king_count = 0;
	int other_piece_count = 0;
    for (int i = 0; i < 64; i++) {
		if (board_piece[i] == KING) {
			king_count++;
		}
        else if (board_piece[i] == PAWN || board_piece[i] == KNIGHT || board_piece[i] == BISHOP || board_piece[i] == ROOK || board_piece[i] == QUEEN) {
			other_piece_count++;
        }
    }
    if (king_count == 2 && other_piece_count == 0) {
		return true; // Csak a ketto kiraly maradt
	}
	return false; // Nem csak a ketto kiraly maradt
}
