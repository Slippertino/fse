#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

namespace fse {

class EngineConfig {

	friend struct nlohmann::adl_serializer<EngineConfig>;

public:
	struct Config {
		std::string name;
		std::string version;
		uint16_t max_responses = 5u;
	};

public:
	static EngineConfig from_file(const std::filesystem::path& path);

	const Config& get_config() const;
	const std::vector<std::string>& get_files() const;

private:
	Config cfg_;
	std::vector<std::string> files_;
};

} // namespace fse