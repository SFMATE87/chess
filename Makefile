CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = chess
SRCS = main.cpp Game.cpp Board.cpp Pieces.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp King.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o

.PHONY: all clean
