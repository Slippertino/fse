#include <gtest/gtest.h>
#include "invertedindex.h"

void test_inverted_index(
	const std::vector<std::string>& contents,
	const std::map<std::string, fse::WordInFiles>& expected
) {
	fse::InvertedIndex index;
	index.set_logging(false);
	index.update(contents);

	for (const auto& w : expected) {
		fse::WordInFiles wif;

		if (index.is_word_exist(w.first)) {
			wif = index.get_word_count(w.first);	
		}

		EXPECT_EQ(wif, w.second);
	}
}

TEST(InvertedIndexTests, Basic) {
	const std::vector<std::string> contents = {
		"milk milk milk milk water water",
		"milk water water",
		"milk milk milk milk milk water water water water water",
		"americano cappuccino"
	};

	const std::map<std::string, fse::WordInFiles> expected = {
		{	"milk",			{	{0, 4}, {1, 1}, {2, 5}	}	},
		{	"water",		{	{0, 2}, {1, 2}, {2, 5}	}	},
		{	"cappuccino",	{	{3, 1}					}	},
		{	"americano",	{	{3, 1}					}	},
	};

	test_inverted_index(contents, expected);
}

TEST(InvertedIndexTests, Empty) {
	const std::vector<std::string> contents = { };

	const std::map<std::string, fse::WordInFiles> expected = {};

	test_inverted_index(contents, expected);
}

TEST(InvertedIndexTests, EmptyContents) {
	const std::vector<std::string> contents = { "", "" };

	const std::map<std::string, fse::WordInFiles> expected = {};

	test_inverted_index(contents, expected);
}

TEST(InvertedIndexTests, MissingWord) {
	const std::vector<std::string> contents = { 
		"a b c d e f g h i j k l",
		"statement",
	};

	const std::map<std::string, fse::WordInFiles> expected = {
		{ "m",			{			}	},
		{ "statement",	{ {1, 1}	}	},
	};

	test_inverted_index(contents, expected);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}