#include "headers.c++"
#pragma once
class Constants {
public:
  static const string savedDataFileName;
  static const char blockDelimiter = '/';
  static const char interGameDelimiter = '#';
  static const char intraGameDelimiter = '_';
};

const string Constants::savedDataFileName = "saved_data.txt";