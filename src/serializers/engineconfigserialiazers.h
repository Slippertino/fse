#pragma once

#include <nlohmann/json.hpp>
#include "../engineconfig.h"

namespace nlohmann {

template<>
struct adl_serializer<fse::EngineConfig::Config> {
	template<class JsonType>
    static void from_json(const JsonType& j, fse::EngineConfig::Config& value) {
		j.at("name").get_to(value.name);
		j.at("version").get_to(value.version);

		if (j.contains("max_responses")) {
			j.at("max_responses").get_to(value.max_responses);
		}
    }
};

template<>
struct adl_serializer<fse::EngineConfig> {
	template<class JsonType>
	static void from_json(const JsonType& j, fse::EngineConfig& value) {
		j.at("config").get_to(value.cfg_);
		j.at("files").get_to(value.files_);
	}
};

} // namespace nlohmann