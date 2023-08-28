#pragma once

#include <audioplugin/core/verify.hpp>
#include <audioplugin/core/register.hpp>




/// @brief
#define REGISTER_PLUGIN(processor_class_m, controller_class_m)              \
    AUDIOPLUGIN_VERIFY_PLUGIN(processor_class_m, controller_class_m)          \
    AUDIOPLUGIN_ADD_PLUGIN(processor_class_m, controller_class_m)             \
    AUDIOPLUGIN_ADD_PLUGIN_AAX_WRAPPER()                                      \
    AUDIOPLUGIN_ADD_PLUGIN_AU2_WRAPPER(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_ADD_PLUGIN_AU3_WRAPPER(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_ADD_PLUGIN_VST2_WRAPPER()