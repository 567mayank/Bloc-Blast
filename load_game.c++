#include "constants.c++"
#include "file_manager.c++"
#include "game.c++"
#pragma once
class LoadGame {
  string savedDataString;
  vector<string> savedGameIds;
  vector<string> savedGameInfos;

  /// this will be used to load the data from the saved data file
  void loadData() {
    FileManager *fileManager = new FileManager();
    fileManager->open(Constants::savedDataFileName, ios::in);
    /// disposing the file manager
    string data = fileManager->readLine();
    delete fileManager;
    this->savedDataString = data;
  }

  /// this will be used to load all the game infos from the saved data string
  void loadAllGameInfos() {
    this->savedGameInfos = Utilities::split(this->savedDataString, Constants::interGameDelimiter);
  }

  /// this will be used to load all the game ids from the saved data string
  void loadAllGameIds() {
    for (string gameInfo : this->savedGameInfos) {
      if (gameInfo.empty()) {
        continue;
      }
      this->savedGameIds.push_back(Utilities::split(gameInfo, Constants::intraGameDelimiter)[0]);
    }
  }

public:
  LoadGame() {
    loadData();
    loadAllGameInfos();
    loadAllGameIds();
    for (string gameId : this->savedGameIds) {
      cout << gameId << endl;
    }
  }

  Game *loadSpecificGameInfo(string gameId) {
    for (string gameInfo : this->savedGameInfos) {
      if (gameInfo.empty()) {
        continue;
      }
      if (Utilities::split(gameInfo, Constants::intraGameDelimiter)[0] == gameId) {
        Game *game = new Game(gameInfo);
        if (game->isGameValid()) {
          printGameLoadedOnTerminal();
          return game;
        }
        printGameLoadFailedOnTerminal();
        delete game;
        return nullptr;
      }
    }
    printGameLoadFailedOnTerminal();
    return nullptr;
  }
};