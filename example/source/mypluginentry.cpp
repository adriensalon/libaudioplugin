

#include "myplugincontroller.h"
#include "mypluginprocessor.h"
#include <audioplugin/audioplugin.hpp>

#if defined(AUDIOPLUGIN_BACKEND_AAX)

// AAX_ADDITIONAL_OUTPUTS_ARRAY(
// 	AAX_ADDITIONAL_OUTPUT("AUX2", 2),
// 	AAX_ADDITIONAL_OUTPUT("AUX3", 2))

// AAX_MIDI_INPUTS_ARRAY(
// 	AAX_MIDI_INPUT(PLUGIN_NAME "MidiInA", 0xffff << 0),
// 	AAX_MIDI_INPUT(PLUGIN_NAME "MidiInB", 0xffff << 1))

// AAX_METERS_ARRAY(
// 	AAX_METER("Output", 555 /* must be a parameter ID for the vu (see again)*/, 1))

AAX_VARIANTS_ARRAY(
	AAX_VARIANT("mono", 1, 1, 0, 0),
	AAX_VARIANT("stereo", 2, 2, 0, 0))

#endif

REGISTER_PLUGIN(vstsync::TestPlugProcessor, vstsync::TestPlugController)