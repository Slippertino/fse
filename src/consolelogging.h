#pragma once

#include "osyncstream.h"

namespace fse {

class ConsoleLogging {
public:
	virtual void set_logging(bool enabled);

protected:
	OSyncStream synccout();
	OSyncStream syncclog();
	OSyncStream synccerr();

private:
	bool logging_enabled_ = true;
};

} // namespace fse