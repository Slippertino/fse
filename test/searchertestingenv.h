#include <gtest/gtest.h>
#include "searcher.h"

class SearcherTestingEnvironment : public testing::Environment {
public:
	SearcherTestingEnvironment() : searcher(index) 
	{ }

	void SetUp() override {
		searcher.set_logging(false);
		index.set_logging(false);

		index.update({
			"london is the capital of great britain",
			"paris is the capital of france",
			"berlin is the capital of germany",
			"rome is the capital of italy",
			"madrid is the capital of spain",
			"lisboa is the capital of portugal",
			"bern is the capital of switzerland",
			"moscow is the capital of russia",
			"kiev is the capital of ukraine",
			"minsk is the capital of belarus",
			"astana is the capital of kazakhstan",
			"beijing is the capital of china",
			"tokyo is the capital of japan",
			"bangkok is the capital of thailand",
			"welcome to moscow the capital of russia the third rome",
			"amsterdam is the capital of netherlands",
			"helsinki is the capital of finland",
			"oslo is the capital of norway",
			"stockholm is the capital of sweden",
			"riga is the capital of latvia",
			"tallinn is the capital of estonia",
		});
	}

public:
	fse::InvertedIndex index;
	fse::Searcher searcher;
};