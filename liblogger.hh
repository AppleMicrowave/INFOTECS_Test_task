#ifndef LIBLOGGER_H
#define LIBLOGGER_H

#include <chrono>
#include <fstream>
#include <string>

// Библиотека - это набор функций, одна структура для сообщения, и перечисление
// для уровней
// У библиотеки одна функциональная идея - записывать сообщения в журнал

enum class MessageLevel { INFO = 1, WARNING, CRITICAL };

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
  Logger(const std::string& filename, const MessageLevel& level);

  void setLevel(const MessageLevel& level);
  MessageLevel getLevel();
  void getMessage(const Message&);
  void writeMessage();
};

void init_log();

#endif
