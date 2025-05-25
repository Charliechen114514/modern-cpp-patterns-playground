#include "logger.h"
#include <mutex>
#include <print>
std::mutex SimpleLogger::logger_lock {}; ///< message locker

// Double Lock is an old stuff
// SimpleLogger* SimpleLogger::simpleLogger = nullptr;

SimpleLogger::SimpleLogger() {
	std::println("[logger: ] Logger init invoke once");
}

SimpleLogger& SimpleLogger::instance() {
	/* Check once */
	// if (!simpleLogger) {
	// 	std::unique_lock<std::mutex> guard_me(logger_lock);
	// 	if (!simpleLogger) {
	// 		simpleLogger = new SimpleLogger;
	// 	}
	// }
	// return simpleLogger;
	static SimpleLogger simpleLogger;
	return simpleLogger;
}

void SimpleLogger::log_messages(const std::string& message) {
	std::println("[logger: ] {}", message);
}