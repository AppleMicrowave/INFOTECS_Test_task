#include <cstdlib>  // for system(clear)
#include <filesystem>
#include <iostream>
#include <sstream>

#include "liblogger.hh"

// Суть приложения - обособленно от библиотеки принимать и передавать сообщения
// менеджеру логов

MessageLevel parseLevel(const std::string& str_value);
std::string levelToStr(const MessageLevel& level);

int main(int argc, char** argv) {
  // arg check
  if (argc <= 1) {
    std::cerr << "Usage: ./app file info|warning|critical\n";
    return -1;
  }

  // file check
  const std::string file = argv[1];
  if (!std::filesystem::exists(file)) {
    std::cerr << "File " << file << " doesn't exist.\n";
    return -2;
  } else {
    if (std::filesystem::path(file).extension().string() != ".txt") {
      std::cerr << "File " << "file" << " isn't a writable type (.txt).\n";
      return -3;
    }
  }

  const MessageLevel defaut_level = parseLevel(argv[2] ? argv[2] : "info");

  Logger log_manager{file, defaut_level};

  std::fstream file_reader;
  file_reader.open(file,
                   std::fstream::in | std::fstream::out | std::fstream::app);

  char choice;
  while (true) {
    choice = 0;
    std::cout << "Current logfile: " << file
              << "\nLog level: " << levelToStr(log_manager.getLevel()) << "\n";
    std::cout << "1. Send log\n";
    std::cout << "2. Change log level\n";
    std::cout << "3. Exit\n:";

    std::cin.get(choice);
    std::cin.ignore(1000, '\n');
    switch (choice) {
      case '1': {
        std::system("clear");

        int level = static_cast<int>(log_manager.getLevel());
        std::cout << "Message importance level(Info - 1, Warning - "
                     "2, Critical - 3), or press Enter to pass\n:";

        std::cout << "\nEnter message: ";
        break;
      }
      case '2': {
        std::system("clear");

        std::cout
            << "Set default importance level(info | warning | critical)\n:";

        std::string input;
        std::getline(std::cin, input);
        log_manager.setLevel(parseLevel(input));

        std::system("clear");
        break;
      }
      case '3':
        goto end_loop;
      default:
        std::system("clear");
        break;
    }
  }
end_loop:
  file_reader.close();

  return 0;
}

MessageLevel parseLevel(const std::string& str_value) {
  MessageLevel level;
  if (str_value == "critical")
    level = MessageLevel::CRITICAL;
  else if (str_value == "warning")
    level = MessageLevel::WARNING;
  else
    level = MessageLevel::INFO;
  return level;
}

std::string levelToStr(const MessageLevel& level_value) {
  std::string string;
  if (level_value == MessageLevel::CRITICAL)
    string = "critical";
  else if (level_value == MessageLevel::WARNING)
    string = "warning";
  else
    string = "info";
  return string;
}
