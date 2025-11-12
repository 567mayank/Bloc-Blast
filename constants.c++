#include "headers.c++"
#pragma once
class Constants {
public:
  static const string savedDataFileName;
  static const char blockDelimiter = '/';
  static const char interGameDelimiter = '#';
  static const char intraGameDelimiter = '_';
  /// this will be used to store the game status
  enum GameStatus {
    NEW_GAME,
    SAVED_GAME
  };
};

const string Constants::savedDataFileName = "saved_data";