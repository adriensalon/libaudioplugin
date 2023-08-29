#pragma once

#include <audioplugin/core/register.hpp>
#include <audioplugin/core/verify.hpp>

/// @brief
#define REGISTER_PLUGIN(processor_class_m, controller_class_m)             \
    AUDIOPLUGIN_VERIFY_PLUGIN(processor_class_m, controller_class_m)       \
    AUDIOPLUGIN_REGISTER_PLUGIN_AAX()                                      \
    AUDIOPLUGIN_REGISTER_PLUGIN_AU2(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_REGISTER_PLUGIN_AU3(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_REGISTER_PLUGIN_VST2()                                     \
    AUDIOPLUGIN_REGISTER_PLUGIN_VST3(processor_class_m, controller_class_m)