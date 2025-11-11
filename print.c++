#include "headers.c++"

void getBoardOnTerminal(vector<vector<int>> board) {
  cout << "Board:" << endl;
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

void getBlockOnTerminal(vector<vector<int>> block) {
  cout << "Block:" << endl;
  for (int i = 0; i < block.size(); i++) {
    for (int j = 0; j < block[i].size(); j++) {
      cout << block[i][j] << " ";
    }
    cout << endl;
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

void printGameSavedOnTerminal() {
  cout << "Game Saved" << endl;
}

void printGameLoadedOnTerminal() {
  cout << "Game Loaded" << endl;
}

void printGameLoadFailedOnTerminal() {
  cout << "Game Load Failed" << endl;
}
