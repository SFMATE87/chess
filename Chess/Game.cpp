#include <iostream>
#include "Game.h"
#include "Board.h"

Game::Game() : board(true), checkmate(false), draw(false)
{
	player1 = "Player 1";
	player2 = "Player 2";
}

void Game::start()
{
	std::cout << "Sakk jatek inditasa!" << std::endl;
	setPlayerNames();
	board.printBoard();
	
}

bool Game::input_converter(const std::string& input, int& from_rank, int& from_file, int& to_rank, int& to_file)
{
	if (input.length() != 4) {
		return false;
	}

	if (input[0] < 'a' || input[0] > 'h' || input[2] < 'a' || input[2] > 'h' ||
		input[1] < '1' || input[1] > '8' || input[3] < '1' || input[3] > '8') {
		return false;
	}

	from_file = letterToIndex(input[0]); // 'a' -> 0, 'b' -> 1, ..., 'h' -> 7
	from_rank = input[1] - '0' - 1; // '1' -> 0
	to_file = letterToIndex(input[2]); // 'a' -> 0, 'b' -> 1, ..., 'h' -> 7 
	to_rank = input[3] - '0' - 1; // '1' -> 0
	
	return true;
}

void Game::move()
{
	std::string input;
	int from_rank = 0, from_file = 0, to_rank = 0, to_file = 0;

	while (true) {
		std::cout << "Kovetkezo lepes: " << (board.getTurnColor() == WHITE ? player1 : player2) << std::endl;
		std::getline(std::cin, input);


		try {
			if (!input_converter(input, from_rank, from_file, to_rank, to_file)) {
				throw std::invalid_argument("Hibas bemenet! Kerem adja meg a lepeset a kovetkezo formatumban: e2e4");
			}


			if (!board.isValidMove(board.getPieceArray(), board.getColorArray(), from_rank, from_file, to_rank, to_file, board.getTurnColor())) {
				throw std::invalid_argument("Hibas lepes! Kerem probalja ujra.");
			};

			//Megnezzuk hogy ha oda lepnenk akkor meg mindig sakk lenne e
			if (board.wouldMoveCasuseCheck(from_rank, from_file, to_rank, to_file, board.getTurnColor())) {
				throw std::invalid_argument("Ezzel a lepessel sakkban maradnal!");
			}

			board.movePiece(from_rank, from_file, to_rank, to_file);
			board.promotion(from_rank, to_rank, to_file);
			bool check = false;

			if (board.isKingInCheck(board.getPieceArray(), board.getColorArray(), board.getTurnColor())) {
				throw std::invalid_argument("Ezzel nem lephetsz mert a kiralyod sakkba kerulne!");
			}

			// Ellenõrizzük, hogy a király sakkban van-e
			Color opponent_color = board.getTurnColor() == WHITE ? BLACK : WHITE;
			if (board.isKingInCheck(board.getPieceArray(), board.getColorArray(), opponent_color)) {
				check = true;

				// Ellenõrizzük, hogy a király mattban van-e
				if (board.isCheckmate(opponent_color)) {
					checkmate = true;
				}
			}
			board.switchTurnColor();
			board.printBoard();

			if (check && !checkmate) {
				std::cout << "Sakk! " << (board.getTurnColor() ? player1 : player2) << " kiralya sakkban van!" << std::endl;
				continue;
			}
			if (checkmate) {
				std::cout << "Matt! " << (board.getTurnColor() ? player2 : player1) << " nyert!" << std::endl;
			}
			if (board.KingDraw(board.getPieceArray(), board.getColorArray())) {
				draw = true;
			}

			break;
		}
		catch (const std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	
}

int Game::letterToIndex(char letter)
{
	switch (letter)
	{
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	default:
		return -1; // Hibás bemenet 
	}
}

void Game::setPlayerNames()
{
	while (true) {
		std::cout << "Kerem adja meg az elso jatekos nevet: ";
		std::getline(std::cin, player1);
		std::cout << "Kerem adja meg a masodik jatekos nevet: ";
		std::getline(std::cin, player2);
		if (player1 != player2) {
			break;
		}
		std::cout << "Nem lehet ugyanaz a jatekos nev" << std::endl << std::endl;
	}
}

bool Game::getCheckMate() const
{
	return checkmate;
}

bool Game::getDraw() const
{
	return draw;
}
