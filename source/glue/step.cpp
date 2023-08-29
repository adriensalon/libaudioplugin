
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

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
            // for (auto& _pair : _result) {
            //     std::cout << _pair.first << std::endl;
            //     for (auto& lol : _pair.second) {
            //         std::cout << lol << std::endl;
            //     }
            // }
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

#if defined(AUDIOPLUGIN_BACKEND_VST2)
#include <public.sdk/source/vst/vst2wrapper/vst2wrapper.h>

VstIntPtr HostCallback (AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt)
{
	VstIntPtr result = 0;

	// Filter idle calls...
	bool filtered = false;
	if (opcode == audioMasterIdle)
	{
		static bool wasIdle = false;
		if (wasIdle)
			filtered = true;
		else
		{
			printf ("(Future idle calls will not be displayed!)\n");
			wasIdle = true;
		}
	}

	// if (!filtered)
	// 	printf ("PLUG> HostCallback (opcode %d)\n index = %d, value = %p, ptr = %p, opt = %f\n", opcode, index, FromVstPtr<void> (value), ptr, opt);

	switch (opcode)
	{
		case audioMasterVersion :
			result = kVstVersion;
			break;
	}

	return result;
}
#endif


#if defined(AUDIOPLUGIN_BACKEND_AAX)

#include <public.sdk/source/vst/aaxwrapper/aaxwrapper.h>


#include "AAX.h"
#include "AAX_Init.h"
#include "acfresult.h"
#include "acfunknown.h"

#endif





int main(int argc, char** argv)
{

    // args
    // 1st is target plugin lib
    // 2nd is external tool command

    using namespace audioplugin::detail;
    std::cout << std::endl;
	
	formatted_args _formatted_args = format_args(argc, argv);
	extracted_args _extracted_args = extract_args(_formatted_args);
	const std::filesystem::path& _plugin_path = _extracted_args.first;
	plugin_library = dylib(_plugin_path);

#if defined(AUDIOPLUGIN_BACKEND_VST2)
    try {

        using vst2_entry_function = AEffect* (*)(audioMasterCallback);
        vst2_entry_function _vst2_plugin_main = nullptr;
        try {
            _vst2_plugin_main = plugin_library.value().get_function<AEffect*(audioMasterCallback)>("VSTPluginMain");
            std::cout << "[==========] Found VSTPluginMain" << std::endl;
        } catch (...) {
            std::cout << "[==========] AEffect* VSTPluginMain(audioMasterCallback) not found" << std::endl;
            try {
                _vst2_plugin_main = plugin_library.value().get_function<AEffect*(audioMasterCallback)>("main"); // main_macho on macos
            	std::cout << "[==========] Found main" << std::endl;
            } catch (...) {
				throw std::exception("AEffect* main(audioMasterCallback) not found");
            }
        }

		AEffect* _effect = _vst2_plugin_main(HostCallback);
		if (!_effect)
		{
			printf ("Failed to create effect instance!\n");
			return 1;
		}
		std::size_t _inputs_count = static_cast<std::size_t>(_effect->numInputs);
		std::cout << "[==========] Found " << std::to_string(_inputs_count) << " audio inputs"<< std::endl;

		std::size_t _outputs_count = static_cast<std::size_t>(_effect->numOutputs);
		std::cout << "[==========] Found " << std::to_string(_outputs_count) << " audio outputs"<< std::endl;

		_effect->processDoubleReplacing(_effect, nullptr, nullptr, 10);

        // auto* ooo2 = plugin_library.value().get_function<Steinberg::IPluginFactory*()>("GetPluginFactory");

    } catch (const std::exception& _exception) {
        std::cout << "[==========] Exception occured in validator executable :" << std::endl;
        std::cout << "[==========] " << _exception.what() << std::endl;
    }
#endif

#if defined(AUDIOPLUGIN_BACKEND_AAX)
    std::cout <<  "AAXXXXXXXXXXX" << std::endl;

	try {

        using aax_entry_function = ACFRESULT (*)(IACFUnknown*, IACFPluginDefinition**);
        aax_entry_function _aax_plugin_main = nullptr;
		_aax_plugin_main = plugin_library.value().get_function<ACFRESULT(IACFUnknown*, IACFPluginDefinition**)>("ACFRegisterPlugin");
		IACFPluginDefinition* _pluginDefinition = nullptr;
		ACFRESULT _result = _aax_plugin_main(nullptr, &_pluginDefinition);
		std::cout << "null object = " << std::to_string(AAX_ERROR_NULL_OBJECT) << std::endl;
		std::cout << "unknown = " << std::to_string(AAX_ERROR_UNKNOWN_EXCEPTION) << std::endl;
		std::cout << "ok = " << std::to_string(ACF_OK) << std::endl;
		std::cout << "unexpected = " << std::to_string(ACF_E_UNEXPECTED) << std::endl;
		std::cout << "result = " << std::to_string(_result) << std::endl;
    } catch (const std::exception& _exception) {
        std::cout << "[==========] Exception occured in validator executable :" << std::endl;
        std::cout << "[==========] " << _exception.what() << std::endl;
    }

#endif

    std::cout << std::endl;
    testing::InitGoogleTest(&argc, argv);
    int _result = RUN_ALL_TESTS();
    std::cout << std::endl;
    if (_result && audioplugin::detail::external_validator_output.has_value()) {
        std::cout << audioplugin::detail::external_validator_output.value() << std::endl;
        return _result;
    }
}