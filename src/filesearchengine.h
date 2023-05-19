#pragma once

#include <future>
#include "engineconfig.h"
#include "invertedindex.h"
#include "searcher.h"
#include "fsetypes.h"
#include "serializers/fsetypesserializers.h"

namespace fse {

class FileSearchEngine : public ConsoleLogging {
public:
	FileSearchEngine();

	void set_logging(bool enabled) override;

	void setup(const EngineConfig& cfg);
	void search(const Request& req, Response& resp);

private:
	void cut_result(QueryResult& res);

	void validate_config(const EngineConfig& cfg);
	void read_file(const std::string& file, std::string& content); 
	std::string build_result_title(size_t query_num);

private:
	static const std::string name_;
	static const std::string version_;

	inline static const size_t max_queries_count_ = 1000;

private:
	EngineConfig cfg_;
	InvertedIndex index_;
	Searcher searcher_;
};

} // namespace fse