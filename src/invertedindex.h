#pragma once

#include <numeric>
#include <thread>
#include <vector>
#include "textparser.h"
#include "consolelogging.h"
#include "indextypes.h"

namespace fse {

class InvertedIndex : public ConsoleLogging {
public:
	bool is_word_exist(const std::string& word) const;
	const WordInFiles& get_word_count(const std::string& word) const;

	void update(const std::vector<std::string>& files_input);

private:
	void index_file(const std::string& content, size_t id, InvertedIndexData& data);

private:
	inline static const size_t max_file_words_count = 1000;
	inline static const size_t max_word_size = 100;

private:
	InvertedIndexData freq_dictionary_;
};

} // namespace fse