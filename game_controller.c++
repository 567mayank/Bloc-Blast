#include "headers.c++"
#include "load_game.c++"
class GameController {
  //// this will be used to store the current game id -- which user wants to play
  string currentGameId = "";

  /// current game status -- which user wants to do either play new or saved game
  Constants::GameStatus currentGameStatus = Constants::GameStatus::NEW_GAME;

  /// this will be used to store the current game
  Game *currentGame = nullptr;

  /// this will be used to store the load game object
  LoadGame *loadGame = nullptr;

  void startLoadingSavedData() {
    this->loadGame = new LoadGame();
  }

  void getUserInputs() {
    //// here we will get user input whether he wants to play new or saved game
    /// if user wants to play new game, then we will start new game flow
    /// if user wants to play saved game, if first check if game id is valid, if valid then start loading saved game flow
    this->currentGameId = "gameId";
    this->currentGameStatus = Constants::GameStatus::SAVED_GAME;
  }

  void initLoadingSavedGame() {
    this->currentGame = loadGame->loadSpecificGameInfo(this->currentGameId);
    if (this->currentGame == nullptr || !this->currentGame->isGameValid()) {
      printGameLoadFailedOnTerminal();
      //// TODO: implement flow for fallback from here -- like asking user to play new game or quit the app
      return;
    }
    /// game loaded successfully
  }

  void initNewGame() {
    /// TODO: implement flow for new game
  }

  void startGameFlow() {
    /// TODO: implement flow for game flow
  }

public:
  void initApp() {
    this->startLoadingSavedData();
    getUserInputs();
    if (this->currentGameStatus == Constants::GameStatus::SAVED_GAME) {
      initLoadingSavedGame();
    } else {
      initNewGame();
    }
    /// start the game flow
    startGameFlow();
  }

  /// destructor to dispose the objects
  ~GameController() {
    if (this->loadGame != nullptr) {
      delete this->loadGame;
    }
    if (this->currentGame != nullptr) {
      delete this->currentGame;
    }
  }
};