#pragma once

#include <public.sdk/source/main/pluginfactory.h>

#include <audioplugin/glue/plugids.hpp>
#include <audioplugin/glue/pluginfo.hpp>

#if defined(AUDIOPLUGIN_BACKEND_AAX)

#include <pluginterfaces/base/futils.h>
#include <public.sdk/source/vst/aaxwrapper/aaxwrapper_description.h>

#define AUDIOPLUGIN_REGISTER_PLUGIN_AAX()                                                                         \
    AAX_Effect_Desc effDesc = {                                                                                   \
        AUDIOPLUGIN_PLUGIN_COMPANY,                                                                               \
        AUDIOPLUGIN_PLUGIN_NAME,                                                                                  \
        CCONST(AUDIOPLUGIN_PLUGIN_COMPANY[0], AUDIOPLUGIN_PLUGIN_COMPANY[1], AUDIOPLUGIN_PLUGIN_COMPANY[2], 'A'), \
        CCONST(AUDIOPLUGIN_PLUGIN_NAME[0], AUDIOPLUGIN_PLUGIN_NAME[1], AUDIOPLUGIN_PLUGIN_NAME[2], 'B'),          \
        AUDIOPLUGIN_PLUGIN_TYPE,                                                                                  \
        { 0 },                                                                                                    \
        AUDIOPLUGIN_PLUGIN_VERSION_MAJOR_INT,                                                                     \
        nullptr,                                                                                                  \
        effPlugins,                                                                                               \
    };                                                                                                            \
    int* forceLinkAAXWrapper = &AAXWrapper_linkAnchor;                                                            \
    AAX_Effect_Desc* AAXWrapper_GetDescription()                                                                  \
    {                                                                                                             \
        memcpy(                                                                                                   \
            effDesc.mVST3PluginID,                                                                                \
            (const char*)AUDIOPLUGIN_PROCESSOR_UID,                                                               \
            sizeof(effDesc.mVST3PluginID));                                                                       \
        return &effDesc;                                                                                          \
    }

#else
#define AUDIOPLUGIN_REGISTER_PLUGIN_AAX()
#endif

#if defined(AUDIOPLUGIN_BACKEND_AUV2)
#define AUDIOPLUGIN_REGISTER_PLUGIN_AU2(processor_class_m, controller_class_m)
// TODO
#else
#define AUDIOPLUGIN_REGISTER_PLUGIN_AU2(processor_class_m, controller_class_m)
#endif

#if defined(AUDIOPLUGIN_BACKEND_AUV3)
#define AUDIOPLUGIN_REGISTER_PLUGIN_AU3(processor_class_m, controller_class_m)
// TODO
#else
#define AUDIOPLUGIN_REGISTER_PLUGIN_AU3(processor_class_m, controller_class_m)
#endif

#if defined(AUDIOPLUGIN_BACKEND_VST2)

#include <public.sdk/source/vst/vst2wrapper/vst2wrapper.h>

#define AUDIOPLUGIN_REGISTER_PLUGIN_VST2()                                                                           \
    ::AudioEffect* createEffectInstance(audioMasterCallback audioMaster)                                             \
    {                                                                                                                \
        return Steinberg::Vst::Vst2Wrapper::create(GetPluginFactory(), AUDIOPLUGIN_PROCESSOR_UID, 666, audioMaster); \
    }

#else
#define AUDIOPLUGIN_REGISTER_PLUGIN_VST2()
#endif

#define AUDIOPLUGIN_REGISTER_PLUGIN_VST3(processor_class_m, controller_class_m) \
    BEGIN_FACTORY_DEF(                                                          \
        AUDIOPLUGIN_PLUGIN_COMPANY,                                             \
        AUDIOPLUGIN_PLUGIN_WEBSITE,                                             \
        "mailto:" AUDIOPLUGIN_PLUGIN_EMAIL)                                     \
    DEF_CLASS2(                                                                 \
        INLINE_UID_FROM_FUID(AUDIOPLUGIN_PROCESSOR_UID),                        \
        PClassInfo::kManyInstances,                                             \
        kVstAudioEffectClass,                                                   \
        AUDIOPLUGIN_PLUGIN_NAME,                                                \
        Vst::kDistributable,                                                    \
        AUDIOPLUGIN_PLUGIN_TYPE,                                                \
        AUDIOPLUGIN_PLUGIN_VERSION,                                             \
        kVstVersionString,                                                      \
        processor_class_m::createInstance)                                      \
    DEF_CLASS2(                                                                 \
        INLINE_UID_FROM_FUID(AUDIOPLUGIN_CONTROLLER_UID),                       \
        PClassInfo::kManyInstances,                                             \
        kVstComponentControllerClass,                                           \
        AUDIOPLUGIN_PLUGIN_NAME "Controller",                                   \
        0,                                                                      \
        "",                                                                     \
        AUDIOPLUGIN_PLUGIN_VERSION,                                             \
        kVstVersionString,                                                      \
        controller_class_m::createInstance)                                     \
    END_FACTORY


#if defined(AUDIOPLUGIN_BACKEND_AAX)

/// @brief
#define AAX_ADDITIONAL_OUTPUT(output_name_m, channels_count_m) \
    AAX_Aux_Desc { output_name_m, channels_count_m }

/// @brief
#define AAX_ADDITIONAL_OUTPUTS_ARRAY(...) \
    AAX_Aux_Desc effAux_stereo[] = { __VA_ARGS__, { nullptr } };

/// @brief
#define AAX_MIDI_INPUT(port_name_m, channel_mask_m) \
    AAX_MIDI_Desc { port_name_m, channel_mask_m }

/// @brief
#define AAX_MIDI_INPUTS_ARRAY(...) \
    AAX_MIDI_Desc effMIDI[] = { __VA_ARGS__, { nullptr } };

/// @brief
#define AAX_METER(meter_name_m, parameter_id_m, is_output_m) \
    AAX_Meter_Desc { meter_name_m, parameter_id_m, 0, is_output_m }

/// @brief
#define AAX_METERS_ARRAY(...) \
    AAX_Meter_Desc effMeters[] = { __VA_ARGS__, { nullptr } };

/// @brief
#define AAX_VARIANT(variant_name_m, input_channels_m, output_channels_m, sidechain_input_channels_m, latency_m) \
    AAX_Plugin_Desc                                                                                              \
    {                                                                                                            \
        "com." AUDIOPLUGIN_PLUGIN_COMPANY "." AUDIOPLUGIN_PLUGIN_NAME "." variant_name_m,                                                \
            AUDIOPLUGIN_PLUGIN_NAME,                                                                                         \
            CCONST(variant_name_m[0], variant_name_m[1], variant_name_m[2], 'A'),                                \
            CCONST(variant_name_m[0], variant_name_m[1], variant_name_m[2], 'B'),                                \
            input_channels_m,                                                                                    \
            output_channels_m,                                                                                   \
            sidechain_input_channels_m,                                                                          \
            latency_m                                                                                            \
    }

/// @brief
#define AAX_VARIANTS_ARRAY(...) \
    AAX_Plugin_Desc effPlugins[] = { __VA_ARGS__, { nullptr } };

#endif