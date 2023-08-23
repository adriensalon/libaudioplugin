#pragma once

#include <public.sdk/source/main/pluginfactory.h>

#include <libplugin/wrapper/vstids.hpp>
#include <libplugin/wrapper/controller.hpp>
#include <libplugin/wrapper/processor.hpp>
#include <libplugin/wrapper/version.hpp>

/// @brief
#define REGISTER_PLUGIN(processor_class_m, controller_class_m)                    \
                                                                                  \
    BEGIN_FACTORY_DEF(PLUGIN_COMPANY,                                   \
        "https://www.mycompanyname.com",                                          \
        "mailto:info@mycompanyname.com")                                          \
                                                                                  \
    DEF_CLASS2(INLINE_UID_FROM_FUID(libplugin::detail::plugin_processor_uid),     \
        PClassInfo::kManyInstances,                                               \
        kVstAudioEffectClass,                                                     \
        PLUGIN_NAME,                                                              \
        Vst::kDistributable,                                                      \
        PLUGIN_TYPE,                                                              \
        PLUGIN_VERSION,                                                         \
        kVstVersionString,                                                        \
        libplugin::detail::plugin_processor<processor_class_m>::createInstance)   \
                                                                                  \
    DEF_CLASS2(INLINE_UID_FROM_FUID(libplugin::detail::plugin_controller_uid),    \
        PClassInfo::kManyInstances,                                               \
        kVstComponentControllerClass,                                             \
        PLUGIN_NAME "Controller",                                                 \
        0,                                                                        \
        "",                                                                       \
        PLUGIN_VERSION,                                                         \
        kVstVersionString,                                                        \
        libplugin::detail::plugin_controller<controller_class_m>::createInstance) \
                                                                                  \
    END_FACTORY

/// @brief
namespace libplugin {



}
