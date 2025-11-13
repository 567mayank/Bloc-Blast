#include "print.c++"
#include "block.c++"
#include "save_game.c++"
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
  int points = 0;

  /// this will be used to store the game data in text format
  string gameDataString;

  /// this will be used to store the validity of the game
  bool isValid = false;

  /// this will be used to generate the game data in text format
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

  /// this will be used to check if the game data is valid
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

  /// this will be called whenever a move is made
  void updateGame() {
    this->generateGameInTextFormat();
    initSaveGameFlow();
    /// add more items later on
  }

  /// this will be called whenever we need to save the game
  void initSaveGameFlow() {
    SaveGame *saveGame = new SaveGame(gameDataString, this->gameId);
    delete saveGame;
  }

public:
  Game(string gameId, int gridSize) {
    this->gameId = gameId;
    this->board = new Block(gridSize);
    this->isValid = true;
    this->updateGame();
  }
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

  string getGameInTextFormat() {
    return this->gameDataString;
  }

  void printBoard() {
    getBlockOnTerminal(this->board->getBlock());
  }

  void printRecommendedBlocks() {
    printRecommendedBlocksOnTerminal(this->recommendedBlocks, " ", "1");
  }

  bool isGameValid() {
    return this->isValid;
  }

  /// destructor to dispose the objects
  ~Game() {
    if (this->board != nullptr) {
      delete this->board;
    }
    for (Block *block : this->recommendedBlocks) {
      if (block != nullptr) {
        delete block;
      }
    }
  }
};