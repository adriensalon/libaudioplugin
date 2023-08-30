#pragma once

#if defined(AUDIOPLUGIN_BACKEND_VST2)

#include <memory>

#define DYLIB_CPP17
#include <dylib.hpp>
#include <gtest/gtest.h>
#include <public.sdk/source/vst/vst2wrapper/vst2wrapper.h>

namespace audioplugin {
namespace validate {

    struct plugin_data {
        plugin_data() = delete;
        plugin_data(const plugin_data& other) = delete;
        plugin_data& operator=(const plugin_data& other) = delete;
        plugin_data(plugin_data&& other) = delete;
        plugin_data& operator=(plugin_data&& other) = delete;
        ~plugin_data();

        plugin_data(const dylib& library);

		bool is_loaded() const;

        AEffect* data;
    };
}
}

#endif