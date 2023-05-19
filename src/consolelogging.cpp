#include "consolelogging.h"

namespace fse {

void ConsoleLogging::set_logging(bool enabled) {
	logging_enabled_ = enabled;
}

OSyncStream ConsoleLogging::synccout() {
	return OSyncStream(std::cout, logging_enabled_);
}

OSyncStream ConsoleLogging::syncclog() {
	return OSyncStream(std::clog, logging_enabled_);
}

OSyncStream ConsoleLogging::synccerr() {
	return OSyncStream(std::cerr, logging_enabled_);
}

} // namespace fse