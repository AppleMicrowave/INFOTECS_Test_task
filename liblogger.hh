#ifndef LIBLOGGER_H
#define LIBLOGGER_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

// Библиотека - это набор функций, одна структура для сообщения, и перечисление
// для уровней
// У библиотеки одна функциональная идея - записывать сообщения в журнал

enum class MessageLevel { INFO = 0, WARNING, CRITICAL };

struct Message {
  std::string text;
  std::chrono::system_clock::time_point time;
  MessageLevel level = MessageLevel::INFO;
};

class Logger {
 private:
  std::string file_name;
  MessageLevel default_level;

 public:
  Logger();

  void setLevel();
  void getMessage(const Message& message);
  void getMessage(const Message& message, const MessageLevel& level);
  void writeMessage();
};

void init_log();

#endif
