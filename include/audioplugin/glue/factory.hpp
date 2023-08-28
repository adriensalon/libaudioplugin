#pragma once

#include <public.sdk/source/main/pluginfactory.h>

#include <audioplugin/glue/pluginfo.h>
#include <audioplugin/glue/plugids.hpp>

#define AUDIOPLUGIN_ADD_PLUGIN(processor_class_m, controller_class_m) \
    BEGIN_FACTORY_DEF(                                              \
        PLUGIN_COMPANY,                                             \
        PLUGIN_WEBSITE,                                             \
        "mailto:" PLUGIN_EMAIL)                                     \
    DEF_CLASS2(                                                     \
        INLINE_UID_FROM_FUID(AUDIOPLUGIN_PROCESSOR_UID),                 \
        PClassInfo::kManyInstances,                                 \
        kVstAudioEffectClass,                                       \
        PLUGIN_NAME,                                                \
        Vst::kDistributable,                                        \
        PLUGIN_TYPE,                                                \
        PLUGIN_VERSION,                                             \
        kVstVersionString,                                          \
        processor_class_m::createInstance)                          \
    DEF_CLASS2(                                                     \
        INLINE_UID_FROM_FUID(AUDIOPLUGIN_CONTROLLER_UID),                \
        PClassInfo::kManyInstances,                                 \
        kVstComponentControllerClass,                               \
        PLUGIN_NAME "Controller",                                   \
        0,                                                          \
        "",                                                         \
        PLUGIN_VERSION,                                             \
        kVstVersionString,                                          \
        controller_class_m::createInstance)                         \
    END_FACTORY

#if defined(LIBAUDIOPLUGIN_BUILD_AAX_WRAPPER)
#include <pluginterfaces/base/futils.h>
#include <public.sdk/source/vst/aaxwrapper/aaxwrapper_description.h>
#define AUDIOPLUGIN_ADD_PLUGIN_AAX_WRAPPER()                                    \
    AAX_Effect_Desc effDesc = {                                               \
        PLUGIN_COMPANY,                                                       \
        PLUGIN_NAME,                                                          \
        CCONST(PLUGIN_COMPANY[0], PLUGIN_COMPANY[1], PLUGIN_COMPANY[2], 'A'), \
        CCONST(PLUGIN_NAME[0], PLUGIN_NAME[1], PLUGIN_NAME[2], 'B'),          \
        PLUGIN_TYPE,                                                          \
        { 0 },                                                                \
        PLUGIN_VERSION_MAJOR_INT,                                             \
        nullptr,                                                              \
        effPlugins,                                                           \
    };                                                                        \
    int* forceLinkAAXWrapper = &AAXWrapper_linkAnchor;                        \
    AAX_Effect_Desc* AAXWrapper_GetDescription()                              \
    {                                                                         \
        memcpy(                                                               \
            effDesc.mVST3PluginID,                                            \
            (const char*)AUDIOPLUGIN_PROCESSOR_UID,                                \
            sizeof(effDesc.mVST3PluginID));                                   \
        return &effDesc;                                                      \
    }
#else
#define AUDIOPLUGIN_ADD_PLUGIN_AAX_WRAPPER()
#endif

#if defined(LIBAUDIOPLUGIN_BUILD_AU2_WRAPPER)
#define AUDIOPLUGIN_ADD_PLUGIN_AU2_WRAPPER(processor_class_m, controller_class_m)
// TODO
#else
#define AUDIOPLUGIN_ADD_PLUGIN_AU2_WRAPPER(processor_class_m, controller_class_m)
#endif

#if defined(LIBAUDIOPLUGIN_BUILD_AU3_WRAPPER)
#define AUDIOPLUGIN_ADD_PLUGIN_AU3_WRAPPER(processor_class_m, controller_class_m)
// TODO
#else
#define AUDIOPLUGIN_ADD_PLUGIN_AU3_WRAPPER(processor_class_m, controller_class_m)
#endif

#if defined(LIBAUDIOPLUGIN_BUILD_VST2_WRAPPER)
#include <public.sdk/source/vst/vst2wrapper/vst2wrapper.h>
#define AUDIOPLUGIN_ADD_PLUGIN_VST2_WRAPPER()                                                                     \
    AudioEffect* createEffectInstance(audioMasterCallback audioMaster)                                          \
    {                                                                                                           \
        return Steinberg::Vst::Vst2Wrapper::create(GetPluginFactory(), AUDIOPLUGIN_PROCESSOR_UID, 666, audioMaster); \
    }

#else
#define AUDIOPLUGIN_ADD_PLUGIN_VST2_WRAPPER()
#endif

