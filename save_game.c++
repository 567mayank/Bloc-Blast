#include "headers.c++"
#include "file_manager.c++"
class SaveGame {
  string data;

  void saveGamesState(string gameId, bool addInMainFile = false) {
    FileManager *fileManager = new FileManager();
    string fileName = Utilities::getFileNameForSpecificGame(gameId);
    if (addInMainFile) {
      fileName = Constants::savedDataFileName;
    }
    fileManager->writeLine(this->data, fileName);
    delete fileManager;
  }

public:
  SaveGame(string data, string gameId, bool addInMainFile = false) {
    this->data = data;
    saveGamesState(gameId, addInMainFile);
  }
};