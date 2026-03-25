#include <iostream>
#include <string>
#include "Game.h"

int main() {
	try {
		Game game;
		game.start();
		while (true) {
			game.move();
			if (game.getCheckMate()) {
				std::cout << "A jateknak vege!" << std::endl;
				break;
			}if (game.getDraw()) {
				std::cout << "Dontetlen!" << std::endl;
				break;
			}
		}
	}
	catch (const std::exception& ex) {
		std::cerr << "Hiba tortent: " << ex.what() << std::endl;
	}
	return 0;
}