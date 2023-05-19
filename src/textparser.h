#pragma once

#include <regex>
#include <string>
#include <vector>

namespace fse {

class TextParser {
public:
	static void parse(
		const std::string& src,
		std::vector<std::string>& dest,
		size_t max_words_count = std::numeric_limits<size_t>::max(),
		size_t max_word_size = std::numeric_limits<size_t>::max()
	);

private:
	static bool is_whitespace(char ch);
	static void skip_whitespaces(const std::string& src, size_t& pos);
	static void skip_word(const std::string& src, size_t& pos);
	static bool validate_word(const std::string& word, size_t max_size);
};

} // namespace fse