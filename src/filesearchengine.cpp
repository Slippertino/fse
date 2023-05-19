#pragma once

#include "filesearchengine.h"

namespace fse {

FileSearchEngine::FileSearchEngine() : searcher_(index_)
{ }

void FileSearchEngine::set_logging(bool enabled) {
	ConsoleLogging::set_logging(enabled);
	index_.set_logging(enabled);
	searcher_.set_logging(enabled);
}

void FileSearchEngine::setup(const EngineConfig& cfg) {
	validate_config(cfg);

	syncclog() << "Starting app " << name_ << " v. " << version_ << "\n";

	cfg_ = cfg;

	auto files_count = cfg_.get_files().size();

	std::vector<std::string> files_input;
	files_input.resize(files_count);

	for (auto i = 0; i < files_count; ++i) {
		read_file(cfg_.get_files()[i], files_input[i]);
	}

	index_.update(files_input);
}

void FileSearchEngine::search(const Request& req, Response& resp) {
	auto queries_count = std::min(max_queries_count_, req.queries.size());

	resp.answers.resize(queries_count);
	std::generate(resp.answers.begin(), resp.answers.end(), [&, n = 0]() mutable {
		return std::make_pair<std::string, QueryResult>(build_result_title(++n), QueryResult{});
	});
	
	for (auto i = 0; i < queries_count;) {
		std::vector<std::pair<std::future<QueryResult>, size_t>> futures{ std::thread::hardware_concurrency() };

		for (auto j = 0; j < futures.size() && i < queries_count; ++j, ++i) {
			futures[j].first = std::async(
				std::launch::async,
				&Searcher::search,
				&searcher_,
				std::cref(req.queries[i])
			);

			futures[j].second = i;
		}

		for (auto& ftr : futures) {
			if (ftr.first.valid()) {
				auto res = ftr.first.get();
				cut_result(res);
				resp.answers[ftr.second].second = std::move(res);
			}
		}
	}
}

void FileSearchEngine::cut_result(QueryResult& res) {
	auto max = cfg_.get_config().max_responses;

	if (res.results.size() <= max) {
		return;
	}

	res.results.erase(std::next(res.results.begin(), max), res.results.end());
}

void FileSearchEngine::validate_config(const EngineConfig& cfg) {
	auto config = cfg.get_config();

	if (config.name != name_) {
		throw std::invalid_argument("Invalid name of engine in config file");
	}

	if (config.version != version_) {
		throw std::invalid_argument("Invalid version of engine in config file");
	}
}

void FileSearchEngine::read_file(const std::string& file, std::string& content) {
	std::ifstream input{ std::filesystem::path{file} };

	if (!input.is_open()) {
		synccerr() << "Could not open file " << file << " for indexing.\n";
		return;
	}

	input.seekg(0, std::ios::end);
	auto count = input.tellg();

	std::vector<char> data;
	data.resize(count);

	input.seekg(0, std::ios::beg);
	input.read(data.data(), count);
	input.close();

	content = std::string{ data.begin(), data.end() };
}

std::string FileSearchEngine::build_result_title(size_t query_num) {
	static const size_t num_length = std::to_string(max_queries_count_ - 1).size();

	auto num = std::to_string(query_num);
	auto title = "request" + std::string(num_length - num.size(), '0') + num;

	return title;
}

} // namespace fse