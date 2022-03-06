#pragma once

#include <fstream>
#include <iostream>

class Logger {
  public:
    static void info(std::string message);
    static void okay(std::string message);
    static void warning(std::string message);
    static void error(std::string message);
};