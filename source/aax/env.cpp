#if defined(AUDIOPLUGIN_BACKEND_AAX)

#include <aax/env.hpp>

namespace audioplugin {
namespace validate {

    plugin_data::~plugin_data()
    {
    }

    plugin_data::plugin_data(const dylib& library)
    {
        std::cout <<  "AAXXXXXXXXXXX" << std::endl;

		try {

			using aax_entry_function = ACFRESULT (*)(IACFUnknown*, IACFPluginDefinition**);
			aax_entry_function _aax_plugin_main = nullptr;
			_aax_plugin_main = library.get_function<ACFRESULT(IACFUnknown*, IACFPluginDefinition**)>("ACFRegisterPlugin");
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
    }

	bool plugin_data::is_loaded() const
	{
		return true;
	}
}
}

#endif