#include "headers.c++"
#include "constants.c++"
#pragma once

class Utilities {
public:
  static vector<string> split(string data, char delimiter) {
    vector<string> result;
    string item = "";

    for (char c : data) {
      if (c == delimiter) {
        result.push_back(item);
        item = "";
        continue;
      }
      item += c;
    }
    // add the last item to the result if delimiter is not present at last
    if (item.length() > 0) {
      result.push_back(item);
    }
    return result;
  }

  static string join(vector<string> data, char delimiter) {
    string result = "";
    for (string item : data) {
      result += item;
      // if the item is not the last item, add the delimiter
      if (item != data.back()) {
        result += delimiter;
      }
    }
    return result;
  }

  static bool isInt(string data) {
    for (char c : data) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }

  static string getFileNameForSpecificGame(string gameId) {
    return Constants::savedDataFileName + "_" + gameId;
  }

  static string addFileExtensionToFileName(string fileName) {
    return fileName + ".txt";
  }
};