#pragma once

#include <audioplugin/glue/factory.hpp>

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