#include "headers.c++"
#include "load_game.c++"
#include "user_input.c++"
class GameController {
  //// this will be used to store the current game id -- which user wants to play
  string currentGameId = "";

  /// current game status -- which user wants to do either play new or saved game
  Constants::GameStatus currentGameStatus = Constants::GameStatus::NEW_GAME;

  /// this will be used to store the current game
  Game *currentGame = nullptr;

  /// this will be used to store the load game object
  LoadGame *loadGame = nullptr;

  /// this will be used to store the user input object
  UserInput *userInput = nullptr;

  void initObjects() {
    this->loadGame = new LoadGame();
    this->userInput = new UserInput();
  }

  void getUserInputs() {
    //// here we will get user input whether he wants to play new or saved game
    /// if user wants to play new game, then we will start new game flow
    /// if user wants to play saved game, if first check if game id is valid, if valid then start loading saved game flow
    Constants::UserInput userInput = this->userInput->askUserToPlayNewGameOrSavedGame();
    if (userInput == Constants::UserInput::PLAY_NEW_GAME) {
      this->currentGameId = this->userInput->askUserForGameIdToPlayNewGame();
      this->currentGameStatus = Constants::GameStatus::NEW_GAME;
    } else {
      this->currentGameId = this->userInput->askUserForGameIdToPlaySavedGame();
      if (!isGameIdAvailableInSavedGames()) {
        /// if game id is not available in saved games, then ask user again to play new game or quit the app
        getUserInputs();
        return;
      };
      this->currentGameStatus = Constants::GameStatus::SAVED_GAME;
    }
  }

  bool isGameIdAvailableInSavedGames() {
    bool isGameIdAvailable = this->loadGame->isGameIdAvailableInSavedGames(this->currentGameId);
    if (!isGameIdAvailable) {
      printGameIdNotAvailableOnTerminal();
      return false;
    }
    return true;
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
    /// creating new game object
    this->currentGame = new Game(this->currentGameId, 8);

    /// getting the saved data string for all games
    /// adding the game id to the saved data string
    string dataToBeSaved = loadGame->getSavedDataStringForAllGames();
    dataToBeSaved += dataToBeSaved.empty() ? "" : string(1, Constants::interGameDelimiter);
    dataToBeSaved += this->currentGameId;

    //// saving game id in main [saved_data] file
    /// just saving the gameID
    /// as all the other data will be saved inside game class itself
    SaveGame *saveGame = new SaveGame(dataToBeSaved, Constants::savedDataFileName, true);
    delete saveGame;
  }

  void startGameFlow() {
    /// TODO: implement flow for game flow
  }

public:
  void initApp() {
    this->initObjects();
    /// TODO: send welcome message on terminal
    /// TODO: print rules on terminal

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
  /// TODO: thia can be done before the [startGameFlow] is called
  ~GameController() {
    if (this->loadGame != nullptr) {
      delete this->loadGame;
    }
    if (this->currentGame != nullptr) {
      delete this->currentGame;
    }
    if (this->userInput != nullptr) {
      delete this->userInput;
    }
  }
};