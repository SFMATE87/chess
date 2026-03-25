# Chess (Console)

> *Written ~1 years ago as one of my first C++ projects — finally documented and uploaded.*

A console-based two-player Chess game written in C++. Supports move input in standard chess notation, checkmate and draw detection, and a full piece hierarchy built with OOP and inheritance.

---

## Backstory

This was one of my early C++ projects. It was my first time working with class inheritance and polymorphism in a real context — each piece type is its own class derived from a common `Pieces` base.

It lived in a Visual Studio project on my hard drive for a year. Uploading it now as a snapshot of where I was when I was just figuring out OOP.

---

## Features

- **All 6 piece types** — Pawn, Rook, Knight, Bishop, Queen, King
- **OOP design** — `Pieces` base class with virtual `isValidMove()`, each piece in its own `.cpp`/`.h`
- **Move validation** — illegal moves are rejected per piece rules
- **Checkmate & draw detection**
- **Standard notation input** — moves entered as e.g. `e2 e4`

---

## Project Structure

```
chess/
├── main.cpp        # Entry point
├── Game.cpp/.h     # Game loop, input handling, player names
├── Board.cpp/.h    # Board state and rendering
├── Pieces.cpp/.h   # Abstract base class for all pieces
├── Pawn.cpp/.h
├── Rook.cpp/.h
├── Knight.cpp/.h
├── Bishop.cpp/.h
├── Queen.cpp/.h
├── King.cpp/.h
├── Makefile        # Build config
└── README.md
```

---

## Building

### Requirements
- GCC with C++17 support (or Visual Studio 2022)

### With Make
```bash
make
```

### Manually
```bash
g++ -std=c++17 -o chess main.cpp Game.cpp Board.cpp Pieces.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp King.cpp
```

## How to Play

1. Run the executable
2. Enter player names when prompted
3. Enter moves in `from to` format — e.g. `e2 e4` moves the piece on e2 to e4
4. The game ends when checkmate or draw is detected

---

## Known Limitations

- Console only — no GUI
- All text is in Hungarian 🇭🇺
- Originally a Visual Studio project (`.vcxproj` not included — source files only)

---