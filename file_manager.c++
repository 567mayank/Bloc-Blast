#include "log.c++"
#include "utilities.c++"
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

  // Write a line to the file
  bool writeLine(const string &text, const string &fname) {
    string fileName = Utilities::addFileExtensionToFileName(fname);
    string fileNameCopy = Utilities::addFileExtensionToFileName(fname + "_copy");

    // Write the data to the fileNameCopy (temp file)
    ofstream tempFile(fileNameCopy, ios::out | ios::trunc);
    if (!tempFile.is_open()) {
      Log::logError("Failed to open temp file '" + fileNameCopy + "' for writing.", "File Manager", "");
      return false;
    }
    tempFile << text;
    tempFile.close();

    /// rename the fileNameCopy to fileName
    if (rename(fileNameCopy.c_str(), fileName.c_str()) != 0) {
      Log::logError("Failed to rename temp file '" + fileNameCopy + "' to '" + fileName + "'", "Saving Game", "File Manager");
      return false;
    }
    return true;
  }

  // Close the file
  void close() {
    if (file.is_open()) {
      file.close();
      Log::logInfo("File closed successfully.", "File Manager", __FILE__, __LINE__);
    }
  }

  // Destructor to auto-close
  ~FileManager() {
    if (file.is_open()) {
      file.close();
    }
  }
};
