#pragma once

#include <audioplugin/core/verify.hpp>
#include <audioplugin/core/register.hpp>



/// @brief
#if !defined(AUDIOPLUGIN_PROCESSOR_UID)
#define AUDIOPLUGIN_PROCESSOR_UID libaudioplugin::detail::processor_uid
#endif

/// @brief
#if !defined(AUDIOPLUGIN_CONTROLLER_UID)
#define AUDIOPLUGIN_CONTROLLER_UID libaudioplugin::detail::controller_uid
#endif

/// @brief
#define REGISTER_PLUGIN(processor_class_m, controller_class_m)              \
    AUDIOPLUGIN_VERIFY_PLUGIN(processor_class_m, controller_class_m)          \
    AUDIOPLUGIN_ADD_PLUGIN(processor_class_m, controller_class_m)             \
    AUDIOPLUGIN_ADD_PLUGIN_AAX_WRAPPER()                                      \
    AUDIOPLUGIN_ADD_PLUGIN_AU2_WRAPPER(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_ADD_PLUGIN_AU3_WRAPPER(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_ADD_PLUGIN_VST2_WRAPPER()