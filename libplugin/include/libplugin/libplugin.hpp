#pragma once

/// @brief
// using namespace Steinberg::Vst;
// using namespace vstsync;
#define REGISTER_PLUGIN(processor_class_m, controller_class_m)   \
                                                                 \
    BEGIN_FACTORY_DEF(LIBPLUGIN_PLUGIN_COMPANY,                  \
        "https://www.mycompanyname.com",                         \
        "mailto:info@mycompanyname.com")                         \
                                                                 \
    DEF_CLASS2(INLINE_UID_FROM_FUID(k##processor_class_m##UID),  \
        PClassInfo::kManyInstances,                              \
        kVstAudioEffectClass,                                    \
        stringPluginName,                                        \
        Vst::kDistributable,                                     \
        wrapperVST3Category,                                     \
        FULL_VERSION_STR,                                        \
        kVstVersionString,                                       \
        processor_class_m::createInstance)                       \
                                                                 \
    DEF_CLASS2(INLINE_UID_FROM_FUID(k##controller_class_m##UID), \
        PClassInfo::kManyInstances,                              \
        kVstComponentControllerClass,                            \
        stringPluginName "Controller",                           \
        0,                                                       \
        "",                                                      \
        FULL_VERSION_STR,                                        \
        kVstVersionString,                                       \
        controller_class_m::createInstance)                      \
                                                                 \
    END_FACTORY

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace libplugin {

// namespace detail {

template <typename processor_t>
struct plugin_interface {

    int test()
    {
        return processor_t::test();
    }
};

// }

}
