#include "constants.c++"
#include "file_manager.c++"
#include "game.c++"
#pragma once
class LoadGame {
  string savedDataStringForAllGames;
  vector<string> savedGameIds;

  /// this will be used to load the data from the saved data file
  void loadData() {
    FileManager *fileManager = new FileManager();
    fileManager->open(Utilities::addFileExtensionToFileName(Constants::savedDataFileName), ios::in);
    /// disposing the file manager
    string data = fileManager->readLine();
    delete fileManager;
    this->savedDataStringForAllGames = data;
  }

  /// this will be used to load all the game ids from the saved data string
  void loadAllGameIds() {
    vector<string> gameIds = Utilities::split(this->savedDataStringForAllGames, Constants::interGameDelimiter);
    for (string gameId : gameIds) {
      if (gameId.empty()) {
        continue;
      }
      this->savedGameIds.push_back(gameId);
    }
  }

  string loadFileForSpecificGame(string gameId) {
    FileManager *fileManager = new FileManager();
    fileManager->open(Utilities::addFileExtensionToFileName(Utilities::getFileNameForSpecificGame(gameId)), ios::in);
    string data = fileManager->readLine();
    delete fileManager;
    return data;
  }

public:
  LoadGame() {
    loadData();
    loadAllGameIds();
  }

  Game *loadSpecificGameInfo(string gameId) {
    string gameInfo = loadFileForSpecificGame(gameId);
    if (gameInfo.empty()) {
      return nullptr;
    }
    Game *game = new Game(gameInfo);
    if (game->isGameValid()) {
      printGameLoadedOnTerminal();
      return game;
    }
    delete game;
    return nullptr;
  }

  bool isGameIdAvailableInSavedGames(string gameId) {
    return find(this->savedGameIds.begin(), this->savedGameIds.end(), gameId) != this->savedGameIds.end();
  }

  string getSavedDataStringForAllGames() {
    return this->savedDataStringForAllGames;
  }
};