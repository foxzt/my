#include <iostream>
#include <memory>

#include "../sylar/log.h"
#include "../sylar/singleton.h"
#include "../sylar/util.h"

int main() {
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->setLevel(sylar::LogLevel::ERROR);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));

    sylar::LogAppender::ptr stda(new sylar::StdoutLogAppender);
    stda->setFormatter(
            std::make_shared<sylar::LogFormatter>("%d%T%p%T%m%n"));
    logger->addAppender(stda);

    sylar::FileLogAppender::ptr file_appender(
            new sylar::FileLogAppender("./log.txt"));
    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(sylar::LogLevel::ERROR);

    logger->addAppender(file_appender);

    logger->setFormatter(std::make_shared<sylar::LogFormatter>(
            "%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));

    SYLAR_LOG_INFO(logger) << "使用流式方式将日志（info）写入到logger";
    SYLAR_LOG_ERROR(logger) << "使用流式方式将日志（error）写入到logger";
    SYLAR_LOG_DEBUG(logger) << "使用流式方式将日志（debug）写入到logger";

    SYLAR_LOG_FMT_ERROR(logger, "测试使用格式化方式将日志写入到logger：%s", "日志内容");

    auto l = sylar::LoggerMgr::GetInstance()->getLogger("日志器");

    SYLAR_LOG_ERROR(l) << "这是一个错误日志测试";

    return 0;
}