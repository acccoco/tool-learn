/**
 * github：https://github.com/gabime/spdlog
 * 文档：https://spdlog.docsforge.com/#basic-usage
 *
 * logger 和 sink 的原理：
 *  Sinks are the objects that actually write the log to their target.
 *  Each sink should be responsible for only single target (e.g file, console, db),
 *  and each sink has its own private instance of formatter object.
 *
 *  Each logger contains a vector of one or morestd::shared_ptr<sink>.
 *  On each log call (if the log level is right) the logger will call the "sink(log_msg)" function on each of them.
 *
 *  spdlog's sinks have _mt (multi threaded) or _st (single threaded) suffixes to indicate the thread safety.
 *  While single threaded sinks cannot be used from multiple threads simultaneously,
 *  they are faster because no locking is employed.
 *
 * 常用的 sinks：
 *  spdlog/sinks/stdout_sinks.h
 *  spdlog/sinks/basic_file_sink.h
 *  spdlog/sinks/stdout_color_sinks.h
 *  spdlog/sinks/ostream_sink.h
 *
 * 格式说明：
 *  默认格式：[2014-10-31 23:46:59.678] [my_loggername] [info] Some message
 *  格式说明：https://spdlog.docsforge.com/v1.x/3.custom-formatting/#pattern-flags
 *  - 通过 set_pattern 来为每个 sink 或 logger 设置格式
 *  - 通过 spdlog::set_pattern 来设置全局的格式
 */

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


/**
 * 使用 sink 来手动创建 logger
 * create logger with 2 targets with different log levels and formats.
 * the console will show only warnings or errors, while the file will log all.
 */
void multi_sink_example()
{
    // stdout 的 sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

    // file sink
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
    file_sink->set_level(spdlog::level::trace);

    // 具有两个 sink 的 logger
    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);
    logger.warn("this should appear in both console and file");
    logger.info("this message should not appear in the console, only in the file");
}


/**
 * 使用工厂函数创建 logger，之后可以在任何地方通过 get 方法获得 logger
 */
void stdout_logger_example()
{
    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_st("console");
    logger->set_level(spdlog::level::debug);
    logger->set_pattern("[%^%n%$] %v");
    std::shared_ptr<spdlog::logger> same_logger = spdlog::get("console");

    logger->info("123");
    same_logger->warn("456");
}


int main()
{
    // multi_sink_example();
    stdout_logger_example();
    return 0;
}