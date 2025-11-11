#include "headers.c++"
#pragma once

/// this will be used to log the errors and warnings
/// all this will be done in a file named [log.txt] (in this file we always add
/// new lines at the end)
///  Terminal wil be occupied by the game so we will log the errors and warnings
///  in this file

class Log {
public:
  static void logError(string error, string header = "Error", string fileName = "") {
    cout << header << " : " << fileName << " : " << error << endl;
  }
};