#include "searchertestingenv.h"

static SearcherTestingEnvironment* env = new SearcherTestingEnvironment;

void test_searcher(
	fse::Searcher& searcher,
	const std::string& query,
	const fse::QueryResult& expected
) {
	auto res = searcher.search(query);

	if (expected.results.size() <= res.results.size()) {
		res.results.erase(std::next(res.results.begin(), expected.results.size()), res.results.end());
	}

	ASSERT_EQ(res, expected);
}

TEST(SearcherTest, Basic) {
	const std::string query = "moscow is the capital of russia";
	const fse::QueryResult expected = {{
		{7,		1.f				},
		{14,	1.f				},
		{0,		0.666666687f	},
		{1,		0.666666687f	},
		{2,		0.666666687f	},
	}};

	test_searcher(env->searcher, query, expected);
}

TEST(SearcherTest, EmptyQuery) {
	const std::string query = "";
	const fse::QueryResult expected = {};

	test_searcher(env->searcher, query, expected);
}

TEST(SearcherTest, SingleUnindexedWord) {
	const std::string query = "programming";
	const fse::QueryResult expected = {};

	test_searcher(env->searcher, query, expected);
}

TEST(SearcherTest, MixedWord) {
	const std::string query = "programming moscow";
	const fse::QueryResult expected = {{
		{7,		1.f},
	}};

	test_searcher(env->searcher, query, expected);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(env);
	return RUN_ALL_TESTS();
}