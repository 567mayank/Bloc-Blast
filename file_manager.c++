#include "log.c++"
#pragma once


class FileManager {
  fstream file;       // manages both read and write
  string filename;    // current file name
  ios::openmode mode; // current mode

public:
  // Open a file with the given mode
  bool open(const string &fname, ios::openmode m) {
    filename = fname;
    mode = m;
    ifstream test(fname);
    if (!test) {
      // File doesn't exist — create it empty
      Log::logError("File doesn't exist - creating it empty", "File Manager", "");
      ofstream create(fname);
      create.close();
    }
    file.open(filename, mode);
    if (!file.is_open()) {
      Log::logError("Could not open file '" + filename + "'", "File Manager", "");
      return false;
    }
    return true;
  }

  // Write a line to the file
  bool writeLine(const string &text) {
    if (!file.is_open() || !(mode & ios::out)) {
      Log::logError("File not open for writing.", "File Manager", "");
      return false;
    }
    file << text << endl;
    return true;
  }

  // Read one line from the file
  string readLine() {
    if (!file.is_open() || !(mode & ios::in)) {
      Log::logError("File not open for reading.", "File Manager", "");
      return "";
    }
    string line = "";
    if (getline(file, line)) {
      return line;
    }
    Log::logError("Failed to read line from file.", "File Manager", "");
    return "";
  }

  // Move cursor to start of file
  void resetCursor() {
    if (file.is_open()) {
      file.clear();  // clear any EOF flags
      file.seekg(0); // move read pointer to beginning
    }
  }

  // Close the file
  void close() {
    if (file.is_open()) {
      file.close();
      Log::logError("File closed successfully.", "File Manager", "");
    }
  }

  // Destructor to auto-close
  ~FileManager() {
    if (file.is_open()) {
      file.close();
    }
  }
};
