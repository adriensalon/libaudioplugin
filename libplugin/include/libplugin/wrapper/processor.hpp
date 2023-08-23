#pragma once

#include <public.sdk/source/vst/vstaudioeffect.h>

/// @brief
namespace libplugin {
	
    // struct ProcessSetup {
    //     int32 processMode; ///< \ref ProcessModes
    //     int32 symbolicSampleSize; ///< \ref SymbolicSampleSizes
    //     int32 maxSamplesPerBlock; ///< maximum number of samples per audio block
    //     SampleRate sampleRate; ///< sample rate
    // };

    // struct ProcessData {
    //     int32 processMode; ///< processing mode - value of \ref ProcessModes
    //     int32 symbolicSampleSize; ///< sample size - value of \ref SymbolicSampleSizes
    //     int32 numSamples; ///< number of samples to process
    //     int32 numInputs; ///< number of audio input busses
    //     int32 numOutputs; ///< number of audio output busses
    //     AudioBusBuffers* inputs; ///< buffers of input busses
    //     AudioBusBuffers* outputs; ///< buffers of output busses

    //     IParameterChanges* inputParameterChanges; ///< incoming parameter changes for this block
    //     IParameterChanges* outputParameterChanges; ///< outgoing parameter changes for this block (optional)
    //     IEventList* inputEvents; ///< incoming events for this block (optional)
    //     IEventList* outputEvents; ///< outgoing events for this block (optional)
    //     ProcessContext* processContext; ///< processing context (optional, but most welcome)
    // }

namespace detail {

    template <typename processor_t>
    struct plugin_processor : public Steinberg::Vst::AudioEffect {
        plugin_processor();
        plugin_processor(const plugin_processor& other) = default;
        plugin_processor& operator=(const plugin_processor& other) = default;
        plugin_processor(plugin_processor&& other) = default;
        plugin_processor& operator=(plugin_processor&& other) = default;
        ~plugin_processor() SMTG_OVERRIDE = default;

        static Steinberg::FUnknown* createInstance(void* context);

        Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

    private:
        processor_t _processor_impl = {};
    };
}
}

#include <libplugin/wrapper/processor.inl>
