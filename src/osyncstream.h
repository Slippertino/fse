#pragma once

#include <mutex>
#include <iostream>

namespace fse {

class OSyncStream {
public:
	OSyncStream() = delete;
	OSyncStream(std::ostream& ostr, bool enabled = true);

	template<class T>
	OSyncStream& operator<<(const T& obj) {
		if (enabled_) {
			ostr_ << obj;
		}

		return *this;
	}

	~OSyncStream();

private:
	inline static std::mutex stream_locker_;
	bool enabled_;
	std::ostream& ostr_;
};

} // namespace fse