#include "constants.c++"
#include "headers.c++"
#include "utilities.c++"

class SaveGame {
  string savedData;

  void saveGame(string data) { this->savedData = data; }

  void saveGamesState(string gameId) {
    vector<string> data = Utilities::split(this->savedData, Constants::interGameDelimiter);
    for (string d : data) {
      vector<string> gameData = Utilities::split(d, Constants::intraGameDelimiter);
      if (gameData.size() == 0) {
        /// print error message
        continue;
      }
      if (gameData[0] != gameId) {
        continue;
      }
    }
    // this->savedData += "#" + gameId + "_" + this->savedData;
  }
};