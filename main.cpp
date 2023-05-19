#include "startup.h"

int main(int argc, char** argv) {
	try {
		fse::Startup st;

		if (argc > 1) st.set_config_path(argv[1]);
		if (argc > 2) st.set_output_path(argv[2]);

		st.run();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << "\n";
	}

	return 0;
}