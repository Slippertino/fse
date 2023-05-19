#pragma once

#include <vector>
#include <string>
#include "searchtypes.h"
#include <nlohmann/json.hpp>

namespace fse {

struct Request {
	std::vector<std::string> queries;
};

struct Response {
	std::vector<std::pair<std::string, QueryResult>> answers;

	bool operator==(const Response& resp) const {
		return answers == resp.answers;
	}
};

} // namespace fse