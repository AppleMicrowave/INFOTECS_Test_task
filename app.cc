#include <bits/chrono.h>  // for system_clock

#include <cstdlib>     // for system
#include <filesystem>  // for path, exists
#include <iostream>    // for operator<<, basic_ostream, char_traits, cout
#include <string>      // for allocator, basic_string, getline, operator!=
#include <thread>      // for thread

#include "liblogger.hh"  // for Logger, Message

Message readInput();

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

  MessageLevel defaut_level = Logger::strToLevel(argv[2] ? argv[2] : "info");
  Logger log_manager{defaut_level};

  char choice;
  while (true) {
    std::system("clear");

    choice = 0;
    std::cout << "Current logfile: " << file
              << "\nLog level: " << Logger::levelToStr(log_manager.getLevel())
              << "\n";
    std::cout << "1. Send log\n";
    std::cout << "2. Change log level\n";
    std::cout << "3. Exit\n>";

    std::cin.get(choice);
    std::cin.ignore(1000, '\n');
    switch (choice) {
      case '1': {
        std::system("clear");

        Message message = readInput();
        if (message.text != "\n")
          // start a new thread to give&write
          std::thread([&log_manager, file, message]() {
            log_manager.writeMessage(file, message);
          }).join();

        break;
      }
      case '2': {
        std::system("clear");

        std::string input;
        std::cout
            << "Set default importance level (info | warning | critical)\n>";

        std::getline(std::cin, input);
        log_manager.setLevel(Logger::strToLevel(input));

        break;
      }
      case '3':
        goto end_loop;
      default:
        break;
    }
  }
end_loop:
  return 0;
}

Message readInput() {
  std::string input;

  std::cout << "Message importance level(info | warning | critical) or Enter "
               "to pass\n>";
  std::getline(std::cin, input);
  MessageLevel level = Logger::strToLevel(input);

  std::cout << "Enter message, then press Enter to send..\n>";
  std::getline(std::cin, input);
  std::string text{input};

  return Message{std::chrono::system_clock::now(), level, text};
}
