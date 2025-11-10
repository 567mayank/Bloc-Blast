#include "block.c++"
#include "constants.c++"
#include "headers.c++"

class LoadGame {
  vector<string> getSavedGameIds() {
    ifstream savedDataFile(Constants::savedDataFileName);
    if (!savedDataFile) {
      Log::logError("Failed to open saved data file", "Load Game", "loadGame");
      return vector<string>();
    }
    string savedData;
    getline(savedDataFile, savedData);
    savedDataFile.close();
    return vector<string>();
  }

public:
  /// block data format looks like this - gridSize/blockData example -
  /// 3/101_111_101
  Block *loadBlock(string blockData) {
    vector<string> blockDataItems = Utilities::split(blockData, Constants::blockDelimiter);

    /// after splitting we should have 2 items - gridSize and blockData
    if (blockDataItems.size() != 2) {
      Log::logError("Invalid block data", "Load Data", "loadGame");
      return nullptr;
    }

    if (!isBlockDataValid(blockDataItems[1], blockDataItems[0])) {
      Log::logError("Invalid block data", "Load Data", "loadGame");
      return nullptr;
    }

    return convertBlockStringDataToBlockObject(blockDataItems[0], blockDataItems[1]);
  }

  bool isBlockDataValid(string blockData, string gridSize) {
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

  Block *convertBlockStringDataToBlockObject(string gridSize, string blockData) {
    return new Block(stoi(gridSize), blockData);
  }
};