#pragma once

#include <set>
#include <algorithm>
#include "searchtypes.h"
#include "invertedindex.h"

namespace fse {

class Searcher : public ConsoleLogging {
public:
	Searcher() = delete;
	Searcher(InvertedIndex& index);

	QueryResult search(const std::string& query);

private:
	void log_finish_message(const std::string& query, size_t count);

	float calculate_file_rank(const std::vector<std::string>& words, size_t file_id);

	void get_included_files(const std::string& word, std::set<size_t>& files);

private:
	inline static const size_t max_query_words_count_ = 10;

private:
	InvertedIndex& index_;
};

} // namespace fse