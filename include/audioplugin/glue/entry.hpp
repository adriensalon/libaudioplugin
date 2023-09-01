#pragma once

#include <audioplugin/glue/pluginfo.hpp>

#if defined(AUDIOPLUGIN_BACKEND_VST2)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2_ENTRY(effect_t)   \
    ::AudioEffect* createEffectInstance(audioMasterCallback audioMaster) \
    {                                                                    \
        return new effect_t();                                           \
    }
#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2_ENTRY(effect_t)
#endif

#if defined(AUDIOPLUGIN_BACKEND_VST3)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_ENTRY(processor_t, processor_uid, controller_t, controller_uid) \
    BEGIN_FACTORY_DEF(                                                                                     \
        AUDIOPLUGIN_PLUGIN_COMPANY,                                                                        \
        AUDIOPLUGIN_PLUGIN_WEBSITE,                                                                        \
        "mailto:" AUDIOPLUGIN_PLUGIN_EMAIL)                                                                \
    DEF_CLASS2(                                                                                            \
        INLINE_UID_FROM_FUID(processor_uid),                                                               \
        PClassInfo::kManyInstances,                                                                        \
        kVstAudioEffectClass,                                                                              \
        AUDIOPLUGIN_PLUGIN_NAME,                                                                           \
        Vst::kDistributable,                                                                               \
        AUDIOPLUGIN_PLUGIN_TYPE,                                                                           \
        AUDIOPLUGIN_PLUGIN_VERSION,                                                                        \
        kVstVersionString,                                                                                 \
        processor_t::createInstance)                                                                       \
    DEF_CLASS2(                                                                                            \
        INLINE_UID_FROM_FUID(controller_uid),                                                              \
        PClassInfo::kManyInstances,                                                                        \
        kVstComponentControllerClass,                                                                      \
        AUDIOPLUGIN_PLUGIN_NAME "Controller",                                                              \
        0,                                                                                                 \
        "",                                                                                                \
        AUDIOPLUGIN_PLUGIN_VERSION,                                                                        \
        kVstVersionString,                                                                                 \
        controller_t::createInstance)                                                                      \
    END_FACTORY

#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_ENTRY(processor_t, processor_uid, controller_t, controller_uid)
#endif

namespace audioplugin {
namespace detail {

}
}