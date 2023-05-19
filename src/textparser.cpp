#include "textparser.h"

namespace fse {

void TextParser::parse(
	const std::string& src,
	std::vector<std::string>& dest,
	size_t max_words_count,
	size_t max_word_size
) {
	size_t i{ 0 };

	for (; i < src.size();) {
		skip_whitespaces(src, i);

		if (i == src.size()) {
			break;
		}

		auto begin = i;
		skip_word(src, i);
		auto word = src.substr(begin, i - begin);

		if (validate_word(word, max_word_size)) {
			dest.push_back(word);

			if (dest.size() == max_words_count) {
				break;
			}
		}
	}
}

bool TextParser::is_whitespace(char ch) {
	static const std::regex ws_pattern = std::regex{ R"(\s)" };

	return std::regex_match(std::string(1, ch), ws_pattern);
}

void TextParser::skip_whitespaces(const std::string& src, size_t& pos) {
	for (; pos < src.size() && is_whitespace(src[pos]); ++pos);
}

void TextParser::skip_word(const std::string& src, size_t& pos) {
	for (; pos < src.size() && !is_whitespace(src[pos]); ++pos);
}

bool TextParser::validate_word(const std::string& word, size_t max_size) {
	static const std::regex pattern = std::regex{ R"(^[a-z]+$)" };

	return word.size() <= max_size && std::regex_match(word, pattern);
}

} // namespace fse