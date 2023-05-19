#pragma once

#include <cmath>
#include <vector>
#include <nlohmann/json.hpp>

namespace fse {

struct RelativeIndex {
	size_t doc_id;
	float rank;

	bool operator==(const RelativeIndex& ri) const {
		return 
			(doc_id == ri.doc_id) && 
			(rank == ri.rank);
	}
};

struct QueryResult {
	std::vector<RelativeIndex> results;

	bool operator==(const QueryResult& qr) const {
		if (results.size() != qr.results.size()) {
			return false;
		}

		for (auto i = 0; i < results.size(); ++i) {
			if (!(results[i] == qr.results[i])) {
				return false;
			}
		}

		return true;
	}
};

} // namespace fse