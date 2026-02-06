#include "liblogger.hh"

#include <ctime>    // for localtime
#include <iomanip>  // for operator<<, put_time

#include "liblogger.hh"

Logger::Logger(MessageLevel level) : default_level(level) {}

MessageLevel Logger::getLevel() const { return default_level; }

void Logger::setLevel(MessageLevel level) { default_level = level; }

void Logger::writeMessage(const std::string& file, const Message& message) {
  std::lock_guard<std::mutex> lock(access_mutex);

  if (message.level < default_level) return;

  std::string level_str;
  switch (message.level) {
    case MessageLevel::INFO:
      level_str = "[INFO]";
      break;
    case MessageLevel::WARNING:
      level_str = "[WARNING]";
      break;
    case MessageLevel::CRITICAL:
      level_str = "[CRITICAL]";
      break;
  }

  auto time = std::chrono::system_clock::to_time_t(message.time);

  file_writer.open(file, std::ofstream::app);
  file_writer << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
              << " " << level_str << " " << message.text << std::endl;
  file_writer.close();
}

MessageLevel Logger::strToLevel(const std::string& str_value) {
  MessageLevel level;
  if (str_value == "critical")
    level = MessageLevel::CRITICAL;
  else if (str_value == "warning")
    level = MessageLevel::WARNING;
  else
    level = MessageLevel::INFO;
  return level;
}

std::string Logger::levelToStr(MessageLevel level_value) {
  std::string string;
  if (level_value == MessageLevel::CRITICAL)
    string = "critical";
  else if (level_value == MessageLevel::WARNING)
    string = "warning";
  else
    string = "info";
  return string;
}
