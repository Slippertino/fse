#include "startup.h"

namespace fse {

void Startup::set_config_path(const std::filesystem::path& cfg) {
	cfg_path_ = cfg;
}

void Startup::set_output_path(const std::filesystem::path& out_path) {
	out_path_ = out_path;
}

void Startup::run() {
	engine_.setup(EngineConfig::from_file(cfg_path_));
	if (!try_open_output()) {
		return;
	}

	std::cout << "Enter path for .json file with request queries or \"exit\" to stop\n";

	for (;;) {
		std::string path;
		std::cout << "Requests source path: ";
		std::getline(std::cin, path);

		if (path == stop_command_) {
			break;
		}

		Request req; Response resp;
		if (!read_request_file(std::filesystem::path{ path }, req)) {
			continue;
		}

		engine_.search(req, resp);

		write_response(resp);
	}
}

bool Startup::read_request_file(const std::filesystem::path& path, Request& req) {
	std::ifstream istr{ path };
	if (!istr.is_open()) {
		std::cerr << "Could not open request file with path: " << path << "\n";
		return false;
	}

	nlohmann::json js;

	try {
		istr >> js;
		js.get_to(req);
	}
	catch (const nlohmann::detail::exception&) {
		istr.close();
		std::cerr << "Error occured while trying to read request file\n";
		return false;
	}

	istr.close();

	return true;
}

bool Startup::try_open_output() {
	std::ofstream ostr{ out_path_ };

	bool res = ostr.is_open();

	if (!ostr.is_open()) {
		std::cerr << "Could not write search results into file with path: " << out_path_ << "\n";
	}
	else {
		ostr.close();
	}
	
	return res;
}

void Startup::write_response(const Response& resp) {
	std::ofstream ostr{ out_path_, std::ios::trunc };

	if (!ostr.is_open()) {
		std::cerr << "Could not write search results into file with path: " << out_path_ << "\n";
		return;
	}

	nlohmann::ordered_json js;
	js = resp;

	auto output = js.dump(4);
	ostr << output;

	ostr.close();

	std::clog << "Response was successfully written into file with path: " << out_path_ << "\n";
}

} // namespace fse