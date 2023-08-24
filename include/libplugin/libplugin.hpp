#pragma once

#include <pluginterfaces/base/fplatform.h>
#include <pluginterfaces/base/funknown.h>
#include <pluginterfaces/vst/vsttypes.h>

/// @brief
#if !defined(PLUGIN_PROCESSOR_UID)
#define PLUGIN_PROCESSOR_UID libplugin::detail::processor_uid
#endif

/// @brief
#if !defined(PLUGIN_CONTROLLER_UID)
#define PLUGIN_CONTROLLER_UID libplugin::detail::controller_uid
#endif

#include <libplugin/libplugin.fwd>

/// @brief
#define REGISTER_PLUGIN(processor_class_m, controller_class_m)    \
    VERIFY_PLUGIN(processor_class_m, controller_class_m)          \
    ADD_PLUGIN(processor_class_m, controller_class_m)             \
    ADD_PLUGIN_AAX_WRAPPER(processor_class_m, controller_class_m) \
    ADD_PLUGIN_AU2_WRAPPER(processor_class_m, controller_class_m) \
    ADD_PLUGIN_AU3_WRAPPER(processor_class_m, controller_class_m) \
    ADD_PLUGIN_VST2_WRAPPER(processor_class_m, controller_class_m)
