#include <iostream>

#include "../sylar/log.h"
#include "../sylar/singleton.h"
#include "../sylar/util.h"

int main() {
  sylar::Logger::ptr logger(new sylar::Logger);
  logger->setLevel(sylar::LogLevel::ERROR);
  logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));

  sylar::LogAppender::ptr stda(new sylar::StdoutLogAppender);
  stda->setFormatter(
      sylar::LogFormatter::ptr(new sylar::LogFormatter("%d%T%p%T%m%n")));
  logger->addAppender(stda);

  sylar::FileLogAppender::ptr file_appender(
      new sylar::FileLogAppender("./log.txt"));
  sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
  file_appender->setFormatter(fmt);
  file_appender->setLevel(sylar::LogLevel::ERROR);

  logger->addAppender(file_appender);

  logger->setFormatter(sylar::LogFormatter::ptr(new sylar::LogFormatter(
      "%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n")));

  SYLAR_LOG_INFO(logger) << "test macro";
  SYLAR_LOG_ERROR(logger) << "test macro error";
  SYLAR_LOG_DEBUG(logger) << "asdasd";

  SYLAR_LOG_FMT_ERROR(logger, "test zzzzz%s", "asdasdasd");

  auto l = sylar::LoggerMgr::GetInstance()->getLogger("llllll");

  SYLAR_LOG_ERROR(l) << "tetetetetete";

  return 0;
}