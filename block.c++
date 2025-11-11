#include "utilities.c++"
#include "constants.c++"
#include "log.c++"
#pragma once
/// this will be used to represent the board and blocks also
/// each block will be represented by a 2D vector of integers
/// 0 will represent empty space
/// 1 will represent a block
// this class will have 2 variables - int blockGridSize and vector<vector<int>>

class Block {
  int blockGridSize;
  vector<vector<int>> block;
  string blockDataString;
  bool isValid = false;

  bool checkIfPositionIsInBlock(int row, int col) {
    if (row < 0 || row >= this->blockGridSize || col < 0 ||
        col >= this->blockGridSize) {
      return false;
    }
    return true;
  }

  string getBlockInTextFormat() {
    string blockData = "";
    for (vector<int> row : this->block) {
      for (int cell : row) {
        blockData += to_string(cell);
      }
    }
    return blockData;
  }

  void generateBlockDataInTextFormat() {
    vector<string> blockData;
    blockData.push_back(to_string(this->blockGridSize));
    blockData.push_back(this->getBlockInTextFormat());
    this->blockDataString = Utilities::join(blockData, Constants::blockDelimiter);
  }

  vector<vector<int>> convertBlockStringDataToBlockVector(string blockData) {
    vector<vector<int>> blockVector;
    for (int i = 0; i < blockData.size(); i += blockGridSize) {
      string blockRow = blockData.substr(i, blockGridSize);
      blockVector.push_back(convertBlockRowStringDataToBlockRowVector(blockRow));
    }
    return blockVector;
  }

  vector<int> convertBlockRowStringDataToBlockRowVector(string blockRow) {
    vector<int> blockRowVector;
    for (char c : blockRow) {
      blockRowVector.push_back(c == '1' ? 1 : 0);
    }
    return blockRowVector;
  }

  /// this will be called whenever the block is updated
  void updateBlock() {
    this->generateBlockDataInTextFormat();
    /// add more items later on
  }

  /// block data format looks like this - gridSize/blockData example -
  /// 3/101_111_101
  bool isBlockDataValid(vector<string> blockDataItems) {
    if (blockDataItems.size() < 2) {
      Log::logError("Invalid block data", "Load Data", "loadGame");
      return false;
    }

    string gridSize = blockDataItems[0];
    string blockData = blockDataItems[1];

    /// gridSize should be a valid integer
    if (!Utilities::isInt(gridSize)) {
      Log::logError("Invalid grid size - not a valid integer", "Load Data", "loadBlock");
      return false;
    }

    int lengthOfblockData = stoi(gridSize) * stoi(gridSize);

    if (blockData.length() != lengthOfblockData) {
      Log::logError("Invalid block data - length mismatch", "Load Data", "load_game");
      return false;
    }

    for (char c : blockData) {
      if (c != '0' && c != '1') {
        Log::logError("Invalid block data - invalid character", "Load Data", "load_game");
        return false;
      }
    }

    return true;
  }

public:
  /// this will be used to load the block from the saved data
  Block(string blockData) {
    vector<string> blockDataItems = Utilities::split(blockData, Constants::blockDelimiter);
    if (!isBlockDataValid(blockDataItems)) {
      Log::logError("Invalid block data", "Block", "Load Game");
      this->isValid = false;
      return;
    }
    this->blockGridSize = stoi(blockDataItems[0]);
    this->block = convertBlockStringDataToBlockVector(blockDataItems[1]);
    this->isValid = true;
    this->updateBlock();
  }

  int getBlockGridSize() {
    return this->blockGridSize;
  }

  vector<vector<int>> getBlock() {
    return this->block;
  }

  bool isPositionInBlockEmpty(int row, int col) {
    if (!checkIfPositionIsInBlock(row, col)) {
      return false;
    }
    return this->block[row][col] == 0;
  }

  /// this will be used to get the block data in text format - gridSize/blockData
  string getBlockDataInTextFormat() {
    return this->blockDataString;
  }

  bool isBlockValid() {
    return this->isValid;
  }
};