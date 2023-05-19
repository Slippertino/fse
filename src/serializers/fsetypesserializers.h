#pragma once

#include <nlohmann/json.hpp>
#include "../fsetypes.h"
#include "searchtypesserializers.h"

namespace nlohmann {

template<>
struct adl_serializer<fse::Request> {
	template<class JsonType>
	static void from_json(const JsonType& j, fse::Request& value) {
		j.at("requests").get_to(value.queries);
	}
};

template<>
struct adl_serializer<fse::Response> {
	template<class JsonType>
	static void from_json(const JsonType& j, fse::Response& value) {
		for (const auto& js : j.at("answers").items()) {
			fse::QueryResult res;
			adl_serializer<fse::QueryResult>::from_json(js.value(), res);
			value.answers.push_back({ js.key(), res });
		}
	}

	static void to_json(ordered_json& j, const fse::Response& value) {
		for (auto i = 0; i < value.answers.size(); ++i) {
			nlohmann::ordered_json js;
			adl_serializer<fse::QueryResult>::to_json(js, value.answers[i].second);
			j["answers"][value.answers[i].first] = js;
		}
	}
};

} // namespace nlohmann