#include "headers.c++"
#include "log.c++"
#include "utilities.c++"
/// this will be used to represent the board and blocks also
/// each block will be represented by a 2D vector of integers
/// 0 will represent empty space
/// 1 will represent a block
// this class will have 2 variables - int blockGridSize and vector<vector<int>>

class Block {
  int blockGridSize;
  vector<vector<int>> block;

  bool checkIfPositionIsInBlock(int row, int col) {
    if (row < 0 || row >= this->blockGridSize || col < 0 ||
        col >= this->blockGridSize) {
      return false;
    }
    return true;
  }

public:
  Block(int blockGridSize) {
    this->blockGridSize = blockGridSize;
    this->block = vector<vector<int>>(blockGridSize, vector<int>(blockGridSize, 0));
  }

  Block(int blockGridSize, string blockData) {
    this->blockGridSize = blockGridSize;
    this->block = convertBlockStringDataToBlockVector(blockData);
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
};