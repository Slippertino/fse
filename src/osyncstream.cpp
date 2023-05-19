#include "osyncstream.h"

namespace fse {

OSyncStream::OSyncStream(std::ostream& ostr, bool enabled) : 
	ostr_(ostr), 
	enabled_(enabled) {
	if (enabled_) {
		stream_locker_.lock();
	}
}

OSyncStream::~OSyncStream() {
	if (enabled_) {
		stream_locker_.unlock();
	}
}

} // namespace fse