#if !defined(AUDIOPLUGIN_BACKEND_AAX) && !defined(AUDIOPLUGIN_BACKEND_VST2)
#error Invalid backend, expected AUDIOPLUGIN_BACKEND_AAX or AUDIOPLUGIN_BACKEND_VST2 to be defined
#endif

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <aax/env.hpp>
#include <vst2/env.hpp>

std::unique_ptr<audioplugin::validate::plugin_data> plugin = nullptr;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
	
	std::vector<std::string> _raw_options(argv + 1, argv + argc);
	if (_raw_options.size() != 1) {
		
		return 1;
	}

	std::filesystem::path _path = _raw_options[0];
	if (!std::filesystem::exists(_path)) {
		
		return 1;
	}

	if (std::filesystem::is_directory(_path)) {

		return 1;
	}

	dylib _library(_path);
    std::cout << std::endl;	

	plugin = std::make_unique<audioplugin::validate::plugin_data>(_library);
    std::cout << std::endl;

	if (!plugin->is_loaded()) {
		
		return 1;
	}

    int _result = RUN_ALL_TESTS();
    std::cout << std::endl;

	return _result;
}