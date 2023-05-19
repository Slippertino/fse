#pragma once

#include <string>
#include "filesearchengine.h"

namespace fse {

class Startup {
public:
	void set_config_path(const std::filesystem::path& cfg);
	void set_output_path(const std::filesystem::path& out_path);

	void run();

private:
	bool try_open_output();
	bool read_request_file(const std::filesystem::path& path, Request& req);
	void write_response(const Response& resp);

private:
	inline static const std::filesystem::path default_cfg_path_ = "config.json";
	inline static const std::filesystem::path default_out_path_ = "answers.json";
	inline static const std::filesystem::path stop_command_		= "exit";

private:
	std::filesystem::path cfg_path_ = default_cfg_path_;
	std::filesystem::path out_path_ = default_out_path_;

	FileSearchEngine engine_;
};

} // namespace fse