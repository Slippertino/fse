#include <gtest/gtest.h>
#include "filesearchengine.h"

template<class T>
void read_json(const std::string& path, T& dst) {
	std::ifstream in{ std::filesystem::path{path} };
	nlohmann::json js;

	in >> js;
	in.close();

	js.get_to(dst);
}

void test_fse(
	const std::string& cfg_path,
	const std::string& reqs_path,
	const std::string& expected_path
) {
	auto cfg = fse::EngineConfig::from_file(cfg_path);

	fse::FileSearchEngine fse;
	fse.set_logging(false);
	fse.setup(cfg);

	fse::Request req;
	read_json<fse::Request>(reqs_path, req);

	fse::Response expected, resp;
	read_json<fse::Response>(expected_path, expected);
	fse.search(req, resp);

	ASSERT_EQ(resp, expected);
}

TEST(FseTests, Basic) {
	test_fse(
		"data/basic_set/config.json",
		"data/basic_set/requests.json",
		"data/basic_set/expected_answers.json"
	);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}