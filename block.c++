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

  /// this will be used to check if the block is used for main board creation
  /// if true, then the block is used for main board creation
  /// if false, then the block is used for recommended blocks
  bool isBlockUsedForMainBoardCreation = false;

  /// this will be used to store the filled count of each row and column
  /// rowFilledCount[i] will store the filled count of the i-th row
  /// columnFilledCount[i] will store the filled count of the i-th column
  /// filled count is the number of 1s in the row or column
  /// size of both the vectors will be equal to the block grid size - initialized to 0
  vector<int> rowFilledCount;
  vector<int> columnFilledCount;

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
    /// TODO: to implement where certain section of block [i.e. board] is cleared as whole row or column is cleared
    this->generateBlockDataInTextFormat();
  }

  /// block data format looks like this - gridSize/blockData example -
  /// 3/101_111_101
  bool isBlockDataValid(vector<string> blockDataItems) {
    if (blockDataItems.size() < 2) {
      Log::logError("Invalid block data", "Load Data", __FILE__, __LINE__);
      return false;
    }

    string gridSize = blockDataItems[0];
    string blockData = blockDataItems[1];

    /// gridSize should be a valid integer
    if (!Utilities::isInt(gridSize)) {
      Log::logError("Invalid grid size - not a valid integer", "Load Data", __FILE__, __LINE__);
      return false;
    }

    int lengthOfblockData = stoi(gridSize) * stoi(gridSize);

    if (blockData.length() != lengthOfblockData) {
      Log::logError("Invalid block data - length mismatch", "Load Data", __FILE__, __LINE__);
      return false;
    }

    for (char c : blockData) {
      if (c != '0' && c != '1') {
        Log::logError("Invalid block data - invalid character", "Load Data", __FILE__, __LINE__);
        return false;
      }
    }

    return true;
  }

  /// this is used to place a block on the board
  pair<int, int> getFirstFilledPositionInBlock() {
    for (int i = 0; i < this->block.size(); i++) {
      for (int j = 0; j < this->block[i].size(); j++) {
        if (this->block[i][j] == 1) {
          return make_pair(i, j);
        }
      }
    }
    return make_pair(-1, -1);
  }

  bool isPositionInBlockEmpty(int row, int col) {
    if (!checkIfPositionIsInBlock(row, col)) {
      return false;
    }
    return this->block[row][col] == 0;
  }

  /// this will be used to initialize the filled count arrays
  void initializeFilledCountArrays() {
    // if the block is not used for main board creation, then we don't need to initialize the filled count arrays
    if (!this->isBlockUsedForMainBoardCreation) {
      return;
    }
    this->rowFilledCount = vector<int>(this->blockGridSize, 0);
    this->columnFilledCount = vector<int>(this->blockGridSize, 0);
  }

  /// this will be used to update the filled count for the block when we are loading the game from the saved data
  void updateFilledCountForSavedBlockAfterLoading() {
    // if the block is not used for main board creation, then we don't need to update the filled count
    if (!this->isBlockUsedForMainBoardCreation) {
      return;
    }
    this->initializeFilledCountArrays();
    for (int i = 0; i < this->blockGridSize; i++) {
      for (int j = 0; j < this->blockGridSize; j++) {
        if (this->block[i][j] == 1) {
          this->rowFilledCount[i]++;
          this->columnFilledCount[j]++;
        }
      }
    }
  }

  void updateFilledCountForBlockAfterPlacingBlockOnBoard(int row, int column) {
    this->rowFilledCount[row]++;
    this->columnFilledCount[column]++;
  }

  void clearFilledRowOrColumn() {
    /// TODO: to implement where certain section of block [i.e. board] is cleared as whole row or column is cleared
  }

public:
  Block(int gridSize, bool isBlockUsedForMainBoardCreation = false) {
    this->blockGridSize = gridSize;
    this->block = vector<vector<int>>(gridSize, vector<int>(gridSize, 0));
    this->isBlockUsedForMainBoardCreation = isBlockUsedForMainBoardCreation;
    this->isValid = true;
    this->initializeFilledCountArrays();
    this->updateBlock();
    Log::logInfo("Block created successfully", "Block constructor", __FILE__, __LINE__);
  }

  /// this will be used to load the block from the saved data
  Block(string blockData, bool isBlockUsedForMainBoardCreation = false) {
    vector<string> blockDataItems = Utilities::split(blockData, Constants::blockDelimiter);
    if (!isBlockDataValid(blockDataItems)) {
      Log::logError("Invalid block data", "Block", __FILE__, __LINE__);
      this->isValid = false;
      return;
    }
    this->blockGridSize = stoi(blockDataItems[0]);
    this->block = convertBlockStringDataToBlockVector(blockDataItems[1]);
    this->isBlockUsedForMainBoardCreation = isBlockUsedForMainBoardCreation;
    this->isValid = true;
    this->updateFilledCountForSavedBlockAfterLoading();
    this->updateBlock();
    Log::logInfo("Block created successfully from saved data", "Block constructor", __FILE__, __LINE__);
  }

  int getBlockGridSize() {
    return this->blockGridSize;
  }

  vector<vector<int>> getBlock() {
    return this->block;
  }

  /// this will be used to get the block data in text format - gridSize/blockData
  string getBlockDataInTextFormat() {
    return this->blockDataString;
  }

  /// this is used to check if the block is valid
  /// this helps when we are loading the game from the saved data
  /// as we are loading the block from the saved data, we need to check if the block is valid - after loading process is completed
  bool isBlockValid() {
    return this->isValid;
  }

  /// this is used to check if the position on the board is empty for the block
  bool isPositionOnBoardEmptyForBlock(Block *block, int row, int column) {
    pair<int, int> firstFilledPosition = block->getFirstFilledPositionInBlock();
    if (firstFilledPosition.first == -1 || firstFilledPosition.second == -1) {
      Log::logError("Invalid block - empty block", "Place Block", __FILE__, __LINE__);
      return false;
    }
    int actualRow = row - firstFilledPosition.first;
    int actualColumn = column - firstFilledPosition.second;
    vector<vector<int>> blockData = block->getBlock();
    for (int i = 0; i < blockData.size(); i++) {
      for (int j = 0; j < blockData[i].size(); j++) {
        if (blockData[i][j] == 0) {
          //// this means the cell in block itself is empty so we can skip it
          continue;
        }
        if (!checkIfPositionIsInBlock(actualRow + i, actualColumn + j)) {
          Log::logError("Invalid position - position is out of range", "Place Block", __FILE__, __LINE__);
          return false;
        }
        //// this means the cell on board is already filled so we return false
        if (!isPositionInBlockEmpty(actualRow + i, actualColumn + j)) {
          Log::logError("Invalid position - position is already filled", "Place Block", __FILE__, __LINE__);
          return false;
        }
      }
    }
    return true; //// this means the position is empty for the block
  }

  //// this will be used to place the block on the board
  //// this will be called only by the [board] of [Game] class
  void placeBlock(Block *blockToPlace, int row, int column) {
    pair<int, int> firstFilledPosition = blockToPlace->getFirstFilledPositionInBlock();
    if (firstFilledPosition.first == -1 || firstFilledPosition.second == -1) {
      Log::logError("Invalid block - empty block", "Place Block", __FILE__, __LINE__);
      return;
    }
    int actualRow = row - firstFilledPosition.first;
    int actualColumn = column - firstFilledPosition.second;
    for (int i = 0; i < blockToPlace->getBlockGridSize(); i++) {
      for (int j = 0; j < blockToPlace->getBlockGridSize(); j++) {
        if (blockToPlace->getBlock()[i][j] == 0) {
          //// this means the cell is empty in block so we can skip it
          continue;
        }
        /// updating the main board with the block data
        this->block[actualRow + i][actualColumn + j] = 1;
        updateFilledCountForBlockAfterPlacingBlockOnBoard(actualRow + i, actualColumn + j);
      }
    }
    this->updateBlock();
  }

  ~Block() {
    this->block.clear();
    this->blockDataString.clear();
    this->isValid = false;
  }
};