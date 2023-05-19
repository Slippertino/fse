#include <gtest/gtest.h>
#include "textparser.h"

template<class... Args>
void test_results(const std::string& src, const std::vector<std::string>& expected, Args... args) {
	std::vector<std::string> res;
	fse::TextParser::parse(src, res, args...);

	ASSERT_EQ(res, expected);
}

TEST(TextParserTests, Basic) {
	const std::string text = "abc a a ab ab";
	const std::vector<std::string> expected = { "abc", "a", "a", "ab", "ab" };

	test_results(text, expected);
}

TEST(TextParserTests, MultiSpacing) {
	const std::string text = "  abc   a   a  ab ab  ";
	const std::vector<std::string> expected = { "abc", "a", "a", "ab", "ab" };

	test_results(text, expected);
}

TEST(TextParserTests, EmptySource) {
	const std::string text = "";
	const std::vector<std::string> expected = { };

	test_results(text, expected);
}

TEST(TextParserTests, NoneWords) {
	const std::string text = "       ";
	const std::vector<std::string> expected = { };

	test_results(text, expected);
}

TEST(TextParserTests, InvalidWords) {
	const std::string text = "ab1 11 abc Abc ab";
	const std::vector<std::string> expected = { "abc", "ab" };

	test_results(text, expected);
}

TEST(TextParserTests, MaxWordsCount) {
	const std::string text = "abc a a ab ab";
	const std::vector<std::string> expected = { "abc", "a", "a" };

	test_results(text, expected, 3);
}

TEST(TextParserTests, MaxWordSize) {
	const std::string text = "abc a a ab ab";
	const std::vector<std::string> expected = { "a", "a", "ab", "ab" };

	test_results(text, expected, 4, 2);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}