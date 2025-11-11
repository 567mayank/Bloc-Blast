#include "print.c++"
#include "block.c++"
#pragma once
class Game {
  /// this will be used to store the game id
  string gameId;

  // board is a 2D vector of integers
  // board[i][j] is the value of the cell in the i-th row and j-th column - 0 is empty, 1 is a piece,
  Block *board;

  /// this will be used to store the recommended blocks for the game
  vector<Block *> recommendedBlocks;

  /// this will be used to store the points of the game
  int points;

  /// this will be used to store the game data in text format
  string gameDataString;

  /// this will be used to store the validity of the game
  bool isValid = false;

  void generateGameInTextFormat() {
    vector<string> gameData;
    gameData.push_back(this->gameId);
    gameData.push_back(to_string(this->points));
    gameData.push_back(this->board->getBlockDataInTextFormat());
    for (Block *block : this->recommendedBlocks) {
      gameData.push_back(block->getBlockDataInTextFormat());
    }
    string gameDataString = Utilities::join(gameData, Constants::intraGameDelimiter);
    this->gameDataString = gameDataString;
  }

  void updateGame() {
    this->generateGameInTextFormat();
    /// add more items later on
  }

public:
  // void initBoard() {
  //   // this->board = vector<vector<int>>(gridSize, vector<int>(gridSize, 0));
  // }

  // Game() {
  //   // this->gridSize = 8;
  //   this->initBoard();
  //   this->updateGame();
  // }

  // Game(int gridSize) {
  //   // this->gridSize = gridSize;
  //   this->initBoard();
  //   this->updateGame();
  // }

  /// this will be used to load the game from the saved data
  Game(string gameData) {
    vector<string> gameDataItems = Utilities::split(gameData, Constants::intraGameDelimiter);
    if (!isGameDataValid(gameDataItems)) {
      this->isValid = false;
      return;
    }
    this->gameId = gameDataItems[0];
    this->points = stoi(gameDataItems[1]);
    this->board = new Block(gameDataItems[2]);
    for (int i = 3; i < gameDataItems.size(); i++) {
      this->recommendedBlocks.push_back(new Block(gameDataItems[i]));
    }

    /// check if the board is valid
    if (!this->board->isBlockValid()) {
      this->isValid = false;
      return;
    }
    /// check if the recommended blocks are valid
    for (Block *block : this->recommendedBlocks) {
      if (!block->isBlockValid()) {
        this->isValid = false;
        return;
      }
    }
    /// calling updateGame to update the game data in text format
    this->isValid = true;
    this->updateGame();
  }

  bool isGameDataValid(vector<string> gameDataItems) {
    if (gameDataItems.size() < 3) {
      // as there should be at least game id, points and board data
      Log::logError("Invalid game data - not enough data", "Load Data", "loadGame");
      return false;
    }
    if (!Utilities::isInt(gameDataItems[1])) {
      Log::logError("Invalid points - not a valid integer", "Load Data", "loadGame");
      return false;
    }
    return true;
  }

  string getGameInTextFormat() {
    return this->gameDataString;
  }

  void printBoard() {
    // getBoardOnTerminal(this->board);
  }

  bool isGameValid() {
    return this->isValid;
  }
};