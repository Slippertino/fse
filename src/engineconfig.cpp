#pragma once

#include "engineconfig.h"
#include "serializers/engineconfigserialiazers.h"

namespace fse {

EngineConfig EngineConfig::from_file(const std::filesystem::path& path) {
	std::ifstream input{ path };

	if (!input.is_open()) {
		throw std::invalid_argument("Impossible to open config file");
	}

	EngineConfig cfg;
	nlohmann::json content;

	try {
		input >> content;
		content.get_to(cfg);
	}
	catch (const nlohmann::detail::exception&) {
		input.close();
		throw std::runtime_error("Error occured while trying to read config file");
	}
	input.close();

	return cfg;
}

const EngineConfig::Config& EngineConfig::get_config() const {
	return cfg_;
}

const std::vector<std::string>& EngineConfig::get_files() const {
	return files_;
}

} // namespace fse