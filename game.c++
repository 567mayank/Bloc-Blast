#include "headers.c++"
#include "print.c++"
#include "block.c++"

class Game {
  // board is a 2D vector of integers
  // board[i][j] is the value of the cell in the i-th row and j-th column - 0 is empty, 1 is a piece,
  vector<vector<int>> board;

  /// gridSize is the size of the board i.e. [8x8]
  int gridSize;

  /// this will be used to store the recommended blocks for the game
  vector<Block *> recommendedBlocks;

  void initBoard() {
    this->board = vector<vector<int>>(gridSize, vector<int>(gridSize, 0));
  }

public:
  Game() {
    this->gridSize = 8;
    this->initBoard();
  }

  Game(int gridSize) {
    this->gridSize = gridSize;
    this->initBoard();
  }

  void printBoard() {
    getBoardOnTerminal(this->board);
  }
};