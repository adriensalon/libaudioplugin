#include <libplugin/libplugin.hpp>

namespace libplugin {

	struct stest {

	};

	plugin_interface<stest> ok;

}

struct demo_plugin {

	void testImpl()
	{
		// if (lolol) {

		// }




	}
	

};


//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#include "../../libplugin/source/wrapper/cids.hpp"
#include "../../libplugin/source/wrapper/controller.hpp"
#include "../../libplugin/source/wrapper/processor.hpp"
#include "../../libplugin/source/wrapper/version.hpp"

#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName LIBPLUGIN_PLUGIN_NAME

using namespace Steinberg::Vst;
using namespace vstsync;


REGISTER_PLUGIN(wrapperProcessor, wrapperController)

