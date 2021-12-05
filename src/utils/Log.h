#ifndef __LOG_H__
#define __LOG_H__

#include <string>

class Log {
 public:
  static void Info(const char* msg);
  static void Debug(const char* msg);
  static void Warn(const char* msg);
  static void Error(const char* msg);
  static void Fatal(const char* msg);

  static void Info(const std::string msg);
  static void Debug(const std::string msg);
  static void Warn(const std::string msg);
  static void Error(const std::string msg);
  static void Fatal(const std::string msg);
};

#endif
