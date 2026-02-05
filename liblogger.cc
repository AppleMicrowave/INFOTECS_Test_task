#include "liblogger.hh"

Logger::Logger(const std::string& filename, const MessageLevel& level)
    : file_name(filename), default_level(level) {}

void Logger::setLevel(const MessageLevel& level) { default_level = level; }

MessageLevel Logger::getLevel() { return default_level; }

void Logger::getMessage(const Message& message) {}

void Logger::writeMessage() {}
