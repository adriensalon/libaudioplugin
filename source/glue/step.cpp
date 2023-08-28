
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#define DYLIB_CPP17
#include <dylib.hpp>
#include <gtest/gtest.h>

#include <audioplugin/glue/step.hpp>

#include <public.sdk/source/main/pluginfactory.h>

namespace audioplugin {
namespace detail {

    static std::optional<dylib> plugin_library = std::nullopt;

    static std::optional<std::string> external_validator_output = std::nullopt;

	// add library load ? idk must be a test

    namespace {

        using formatted_args = std::unordered_map<std::string, std::vector<std::string>>;

        struct formatting_exception final : public std::exception {
            const char* what() const noexcept
            {
                return "okokokk";
            }
        };

        formatted_args format_args(int argc, char* argv[])
        {
            formatted_args _result;
            std::vector<std::string> _raw_options(argv + 1, argv + argc);
            std::string _last_command;
            for (std::string& _raw_option : _raw_options) {
                if (!_raw_option.empty()) {
                    if (_raw_option[0] == '-') {
                        _last_command = _raw_option.substr(1, _raw_option.length() - 1);
                    } else {
                        if (_last_command.empty()) {
                            throw formatting_exception();
                        }
                        _result[_last_command].push_back(_raw_option);
                    }
                }
            }
            for (auto& _pair : _result) {
                std::cout << _pair.first << std::endl;
                for (auto& lol : _pair.second) {
                    std::cout << lol << std::endl;
                }
            }
            return _result;
        }

        using extracted_args = std::pair<std::filesystem::path, std::optional<std::string>>;

        struct extracting_exception final : public std::exception {
            const char* what() const noexcept
            {
                return "okokokk";
            }
        };

        extracted_args extract_args(const formatted_args& args)
        {
            extracted_args _result;
            std::size_t _commands_count = args.size();
            if (_commands_count < 1 || _commands_count > 2) {
                throw extracting_exception();
            }
            if (args.find("plugin") == args.end()) {
                throw extracting_exception();
            }
            if (args.at("plugin").size() != 1) {
                throw extracting_exception();
            }
            _result.first = args.at("plugin").at(0);
            // if (args.find("command") != args.end()) {
            // 	if (args.at("command").size() != 1) {
            // 		throw extracting_exception();
            // 	}
            // 	_result.second = std::nullopt;
            // } else {
            // 	_result.second = args.at("command").at(0);
            // }
            return _result;
        }

    }
}
}
#include <public.sdk/source/vst/vst2wrapper/vst2wrapper.h>

int main(int argc, char** argv)
{

    // args
    // 1st is target plugin lib
    // 2nd is external tool command

    using namespace audioplugin::detail;

    try {
        formatted_args _formatted_args = format_args(argc, argv);
        extracted_args _extracted_args = extract_args(_formatted_args);
        const std::filesystem::path& _plugin_path = _extracted_args.first;
        const std::optional<std::string>& _external_command = _extracted_args.second;

        // std::cout << PLUGIN_COMPANY << "plugin path = " << _plugin_path << std::endl;
        // std::cout << "external_validator_path = " << _external_validator_path << std::endl;

		plugin_library = dylib(_plugin_path);
		auto* ooo2 = plugin_library.value().get_function<Steinberg::IPluginFactory*()>("GetPluginFactory");
		auto* ooo = plugin_library.value().get_function<AEffect*(audioMasterCallback)>("VSTPluginMain");

    } catch (const std::exception& _exception) {
        std::cout << "-- [libaudioplugin] Exception occured in validator executable :" << std::endl;
        std::cout << "-- [libaudioplugin] " << _exception.what() << std::endl;
    }

    std::cout << std::endl;
    testing::InitGoogleTest(&argc, argv);
    int _result = RUN_ALL_TESTS();
    std::cout << std::endl;
    if (_result && audioplugin::detail::external_validator_output.has_value()) {
        std::cout << audioplugin::detail::external_validator_output.value() << std::endl;
        return _result;
    }
}