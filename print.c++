#include "headers.c++"
#include "block.c++"

void getBlockOnTerminal(vector<vector<int>> block, string zeroSymbol = "0", string oneSymbol = "1") {
  cout << "Block:" << endl;
  for (int i = 0; i < block.size(); i++) {
    for (int j = 0; j < block[i].size(); j++) {
      cout << block[i][j] << " ";
    }
    cout << endl;
  }
}

void printRecommendedBlocksOnTerminal(vector<Block *> recommendedBlocks, string zeroSymbol = "0", string oneSymbol = "1") {
  for (int i = 0; i < recommendedBlocks.size(); i++) {
    Block *block = recommendedBlocks[i];
    cout << "Recommended Block " << i + 1 << ":" << endl;
    getBlockOnTerminal(block->getBlock(), zeroSymbol, oneSymbol);
  }
}

void printWrongPositionEnteredOnTerminal() {
  cout << "Wrong position entered -- this position is not on the board" << endl;
}

void printPositionAlreadyFilledOnTerminal() {
  cout << "Position already filled -- this position is already filled with a block" << endl;
}

void printNotPossibleOnTerminal() {
  cout << "This move is not possible -- as the block is not placed in a valid position" << endl;
}

void printGameOverOnTerminal() {
  cout << "Game Over -- as no space is left on the board" << endl;
}

//// Game Save and Load related messages ---------------------------------------

void printGameSavedOnTerminal() {
  cout << "Game Saved" << endl;
}

void printGameSavedFailedOnTerminal() {
  cout << "Game Save Failed" << endl;
}

void printGameLoadedOnTerminal() {
  cout << "Game Loaded" << endl;
}

void printGameLoadFailedOnTerminal() {
  cout << "Game Load Failed" << endl;
}

void printGameIdNotAvailableOnTerminal() {
  cout << "Game Id Not Available in Saved Games -- Please try again" << endl;
}
