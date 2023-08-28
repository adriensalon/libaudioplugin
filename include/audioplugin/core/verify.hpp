#pragma once

#include <audioplugin/glue/detection.hpp>

/// @brief
#define AUDIOPLUGIN_VERIFY_PLUGIN(vst3_processor_m, vst3_controller_m)         \
    static_assert(audioplugin::is_plugin_verified<vst3_processor_m, vst3_controller_m>());

namespace audioplugin {

	/// @brief
	/// @details
	/// @tparam vst3_processor_t
	/// @tparam vst3_controller_t
    template <typename vst3_processor_t, typename vst3_controller_t>
    constexpr bool is_plugin_verified()
    {
		// https://marcofoco.com/blog/2016/10/03/the-power-of-devirtualization/
		
        // has processor createInstance
        // has processor initialize
        // has processor initialize
        return true;
    }

}