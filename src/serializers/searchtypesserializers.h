#pragma once

#include <nlohmann/json.hpp>
#include "../searchtypes.h"

namespace nlohmann {

template<>
struct adl_serializer<fse::RelativeIndex> {
	template<class JsonType>
	static void from_json(const JsonType& j, fse::RelativeIndex& value) {
		j.at("docid").get_to(value.doc_id);
		j.at("rank").get_to(value.rank);
	}

	static void to_json(ordered_json& j, const fse::RelativeIndex& value) {
		j["docid"] = value.doc_id;
		j["rank"] = value.rank;
	}
};

template<>
struct adl_serializer<fse::QueryResult> {
	template<class JsonType>
	static void from_json(const JsonType& j, fse::QueryResult& value) {
		auto result = j.at("result").get<std::string>();

		if (result == "false") {
			return;
		}

		if (j.contains("relevance")) {
			j.at("relevance").get_to(value.results);
			return;
		}

		fse::RelativeIndex res;
		adl_serializer<fse::RelativeIndex>::from_json(j, res);
		value.results.push_back(std::move(res));
	}

	static void to_json(ordered_json& j, const fse::QueryResult& value) {
		if (value.results.empty()) {
			j["result"] = "false";
			return;
		}

		j["result"] = "true";

		if (value.results.size() == 1) {
			j["docid"] = value.results[0].doc_id;
			j["rank"] = value.results[0].rank;
			return;
		}

		j["relevance"] = value.results;
	}
};

} // namespace nlohmann