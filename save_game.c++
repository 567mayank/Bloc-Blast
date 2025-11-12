#include "headers.c++"
#include "file_manager.c++"
class SaveGame {
  string data;

  void saveGamesState(string gameId) {
    FileManager *fileManager = new FileManager();
    fileManager->writeLine(this->data, Utilities::getFileNameForSpecificGame(gameId));
    delete fileManager;
  }

public:
  SaveGame(string data, string gameId) {
    this->data = data;
    saveGamesState(gameId);
  }
};