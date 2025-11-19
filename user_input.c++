#include "headers.c++"
#include "constants.c++"
#include "utilities.c++"
#pragma once

class UserInput {
  /// this will be used to ask user to re-enter input - if user enters invalid input
  string askUserToReEnterInput(string message = "Please re-enter your input: ") {
    cout << "Invalid input. " << message;
    string input;
    cin >> input;
    return input;
  }

  string askUserForInput(string message = "Please enter your input: ") {
    cout << message;
    string input;
    cin >> input;
    return input;
  }

  bool validateGameId(string gameId) {
    // game id cannot be empty
    if (gameId.empty()) {
      return false;
    }
    // game id cannot contain white space
    if (gameId.find(Constants::whiteSpace) != string::npos) {
      return false;
    }
    // game id cannot contain intra game delimiter
    if (gameId.find(Constants::intraGameDelimiter) != string::npos) {
      return false;
    }
    // game id cannot contain block delimiter
    if (gameId.find(Constants::blockDelimiter) != string::npos) {
      return false;
    }
    // game id cannot contain inter game delimiter
    if (gameId.find(Constants::interGameDelimiter) != string::npos) {
      return false;
    }
    return true;
  }

public:
  Constants::UserInput askUserToPlayNewGameOrSavedGame() {
    string input = askUserForInput("Enter 'n' to play new game or 's' to play saved game: ");
    while (true) {
      if (input == "n" || input == "N") {
        return Constants::UserInput::PLAY_NEW_GAME;
      } else if (input == "s" || input == "S") {
        return Constants::UserInput::PLAY_SAVED_GAME;
      }
      input = askUserToReEnterInput("Either enter 'n' or 's' only: ");
    }
    return Constants::UserInput::PLAY_NEW_GAME;
  }

  string askUserForGameIdToPlayNewGame() {
    string gameId = askUserForInput("Create a new game id to play new game: ");
    while (true) {
      if (!validateGameId(gameId)) {
        gameId = askUserToReEnterInput("Enter Game Id Again without any white space, " + string(1, Constants::intraGameDelimiter) + ", " + string(1, Constants::blockDelimiter) + " or " + string(1, Constants::interGameDelimiter) + ": ");
      } else {
        return gameId;
      }
    }
    return "";
  }

  string askUserForGameIdToPlaySavedGame() {
    string gameId = askUserForInput("Enter the game id to load saved game: ");
    while (true) {
      if (!validateGameId(gameId)) {
        gameId = askUserToReEnterInput("Enter Game Id Again without any white space, " + string(1, Constants::intraGameDelimiter) + ", " + string(1, Constants::blockDelimiter) + " or " + string(1, Constants::interGameDelimiter) + ": ");
      } else {
        return gameId;
      }
    }
    return "";
  }

  string askUserForPositionToPlaceBlock() {
    return askUserForInput("Enter the position to place the block format (blockNumber_row_column) i.e. 1_2_3: ");
  }
};