#include "Logger.hpp"

void Logger::info(std::string message) {
  std::cout << "\033[34m [ INFO ]\033[0m " << message << '\n';
}

void Logger::okay(std::string message) {
  std::cout << "\033[32m [ OK ]\033[0m " << message << '\n';
}

void Logger::warning(std::string message) {
  std::cout << "\033[33m [ WARNING ]\033[0m " << message << '\n';
}

void Logger::error(std::string message) {
  std::cout << "\033[31m [ ERROR ]\033[0m " << message << '\n';
}