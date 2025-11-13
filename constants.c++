#include "headers.c++"
#pragma once
class Constants {
public:
  static const string savedDataFileName;
  static const char blockDelimiter = '/';
  static const char interGameDelimiter = '#';
  static const char intraGameDelimiter = '_';
  static const char whiteSpace = ' ';
  /// this will be used to store the game status
  enum GameStatus {
    NEW_GAME,
    SAVED_GAME
  };

  /// user input constants
  enum UserInput {
    PLAY_NEW_GAME,
    PLAY_SAVED_GAME,
    INVALID_INPUT
  };
};

const string Constants::savedDataFileName = "saved_data";