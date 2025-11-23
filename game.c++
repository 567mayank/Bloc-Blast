#include "print.c++"
#include "block.c++"
#include "save_game.c++"
#include "user_input.c++"
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

  /// this will be used to store the user input object
  UserInput *userInput = nullptr;

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

  /// this will be called whenever we need to get user input to place a block
  /// it will validate the input and return the input if valid
  /// or else this function will keep asking user to enter input(recursively) until valid input is entered
  string getUserInputToPlaceBlock() {
    string input = this->userInput->askUserForPositionToPlaceBlock();
    if (!validateUserInputToPlaceBlock(input)) {
      return getUserInputToPlaceBlock();
    }
    return input;
  }

  bool validateUserInputToPlaceBlock(string position) {
    int blockNumber = 0;
    int row = 0;
    int column = 0;

    //// validating the position is not empty
    if (position.empty()) {
      Log::logError("Invalid input - empty input", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }
    if (position.find(Constants::whiteSpace) != string::npos) {
      Log::logError("Invalid input - white space found", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }
    vector<string> positionItems = Utilities::split(position, Constants::intraGameDelimiter);
    if (positionItems.size() != 3) {
      Log::logError("Invalid input - position items size mismatch expected 3 but got " + to_string(positionItems.size()), "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }

    //// validating the block number is a valid integer
    if (!Utilities::isInt(positionItems[0])) {
      Log::logError("Invalid input - block number not a valid integer", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }
    if (!Utilities::isInt(positionItems[1])) {
      Log::logError("Invalid input - row not a valid integer", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }
    if (!Utilities::isInt(positionItems[2])) {
      Log::logError("Invalid input - column not a valid integer", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }

    //// converting the string items to integers - to make it 0 based indexing
    blockNumber = stoi(positionItems[0]) - 1;
    row = stoi(positionItems[1]) - 1;
    column = stoi(positionItems[2]) - 1;

    //// validating the numbers are in range
    if (blockNumber >= this->recommendedBlocks.size() || blockNumber < 0) { // as we are using 1 based indexing for inputs
      Log::logError("Invalid input - block number out of range", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }
    if (row >= this->board->getBlockGridSize() || row < 0) { // as we are using 1 based indexing for inputs
      Log::logError("Invalid input - row out of range", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }
    if (column >= this->board->getBlockGridSize() && column < 0) {
      Log::logError("Invalid input - column out of range", "Validate User Input to Place Block", __FILE__, __LINE__);
      return false;
    }

    //// validating the position is empty for the block - where user wants to place the block
    if (!validatePositionOnBoardIsEmptyForBlock(blockNumber, row, column)) {
      return false;
    }
    Log::logInfo("Valid input - position is empty for the block", "Validate User Input to Place Block", __FILE__, __LINE__);
    return true;
  }

  bool validatePositionOnBoardIsEmptyForBlock(int blockNumber, int row, int column) {
    return this->board->isPositionOnBoardEmptyForBlock(recommendedBlocks[blockNumber], row, column);
  }

  void placeBlockOnBoard(string position) {
    int blockNumber = 0;
    int row = 0;
    int column = 0;
    vector<string> positionItems = Utilities::split(position, Constants::intraGameDelimiter);
    /// converting user input to 0 basec indexing
    blockNumber = stoi(positionItems[0]) - 1;
    row = stoi(positionItems[1]) - 1;
    column = stoi(positionItems[2]) - 1;

    /// placing the block on the board
    this->board->placeBlock(recommendedBlocks[blockNumber], row, column);

    /// removing the block from the recommended blocks
    removeBlockFromRecommendedBlocks(blockNumber);
  }

  void removeBlockFromRecommendedBlocks(int blockNumber) {
    delete this->recommendedBlocks[blockNumber];
    this->recommendedBlocks.erase(this->recommendedBlocks.begin() + blockNumber);
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

  void startGame() {
    this->userInput = new UserInput();
    while (true) {
      printBoard();
      printRecommendedBlocks();
      string input = getUserInputToPlaceBlock();
      placeBlockOnBoard(input);
      updateGame();
    }
    printGameOverOnTerminal();
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