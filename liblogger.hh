#ifndef LIBLOGGER_H
#define LIBLOGGER_H

#include <bits/chrono.h>  // for system_clock

#include <fstream>  // for basic_ofstream, ofstream
#include <mutex>    // for mutex
#include <string>   // for string, basic_string

enum class MessageLevel { INFO = 1, WARNING, CRITICAL };

struct Message {
  std::chrono::system_clock::time_point time;
  MessageLevel level = MessageLevel::INFO;
  std::string text;
};

class Logger {
 private:
  std::ofstream file_writer;
  std::mutex access_mutex;
  MessageLevel default_level;

 public:
  Logger(MessageLevel level);

  MessageLevel getLevel() const;
  void setLevel(MessageLevel level);
  void writeMessage(const std::string& file, const Message& message);

  // utils
  static MessageLevel strToLevel(const std::string& str_value);
  static std::string levelToStr(MessageLevel level);
};

#endif
