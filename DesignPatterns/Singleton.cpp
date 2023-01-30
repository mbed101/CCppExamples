#include <iostream>
#include <string>

class Logger {
  private:
    static Logger *instance;
    Logger() {}

  public:
    static Logger *getInstance() {
      if (!instance)
        instance = new Logger();
      return instance;
    }

    void logMessage(std::string message) {
      std::cout << "Log: " << message << std::endl;
    }
};

Logger *Logger::instance = nullptr;

int main() {
  Logger *logger = Logger::getInstance();
  logger->logMessage("This is a log message");
  return 0;
}
