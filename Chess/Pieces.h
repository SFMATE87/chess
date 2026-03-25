#pragma once
#include <iostream>
#include "Board.h"

class Pieces {  
protected:  
   char symbol;  
   Color color;  

public:  
	Pieces(char symbol, Color color);
   virtual ~Pieces() = default;  
   virtual bool isValidMove(const int board_color[64], int from_rank, int from_file, int to_rank, int to_file, const Board& board) const = 0;  
};