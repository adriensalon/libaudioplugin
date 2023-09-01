#pragma once

namespace audioplugin {
namespace detail {

#if defined(AUDIOPLUGIN_BACKEND_VST2)

    template <typename state_t, typename processor_t, typename viewer_t>
	backend_vst2_effect<state_t, processor_t, viewer_t>::backend_vst2_effect(audioMasterCallback audioMaster)
	{
		_state = std::make_unique<state_t>(); // we add all the parameters to the manager
		_manager.build(); // we reorder them and now we can not add new parameters
		_state.reset(); // we do not need this shallow data anymore
		
		_processor = std::make_unique<processor_t>();
		_process_context = std::make_unique<process_context<state_t>>();
	}

    template <typename state_t, typename processor_t, typename viewer_t>
	backend_vst2_effect<state_t, processor_t, viewer_t>::~backend_vst2_effect()
	{

	}

    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) override
	{
		// pops parameter updates from the queue
		// updates
		_processor->update(_process_context.get());
	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::setProgramName(char* name) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::getProgramName(char* name) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::setParameter(VstInt32 index, float value) override
	{
		_manager.set_normalized_from_host_32(static_cast<std::size_t>(index), value); // pushes new parameter value to the queue		
	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	float backend_vst2_effect<state_t, processor_t, viewer_t>::getParameter(VstInt32 index) override
	{
		_manager.synchronize_from_host();
		return _manager.get_normalized_from_host_32(static_cast<std::size_t>(index));
	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::getParameterLabel(VstInt32 index, char* label) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::getParameterDisplay(VstInt32 index, char* text) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	void backend_vst2_effect<state_t, processor_t, viewer_t>::getParameterName(VstInt32 index, char* text) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	bool backend_vst2_effect<state_t, processor_t, viewer_t>::getEffectName(char* name) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	bool backend_vst2_effect<state_t, processor_t, viewer_t>::getVendorString(char* text) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	bool backend_vst2_effect<state_t, processor_t, viewer_t>::getProductString(char* text) override
	{

	}
	
    template <typename state_t, typename processor_t, typename viewer_t>
	VstInt32 backend_vst2_effect<state_t, processor_t, viewer_t>::getVendorVersion() override
	{

	}

#endif

#if defined(AUDIOPLUGIN_BACKEND_VST3)

    template <typename state_t, typename processor_t>
    backend_vst3_processor<state_t, processor_t>::backend_vst3_processor()
    {
        setControllerClass(backend_vst3_controller_uid);
    }

    template <typename state_t, typename processor_t>
    backend_vst3_processor<state_t, processor_t>::~backend_vst3_processor() SMTG_OVERRIDE
    {
    }

    template <typename state_t, typename processor_t>
    static Steinberg::FUnknown* backend_vst3_processor<state_t, processor_t>::createInstance(void* context)
    {
        // ici on initialise nos trucs
        (void)context;
        return (Steinberg::Vst::IAudioProcessor*)new backend_vst3_processor<state_t, processor_t>;
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE
    {
        Steinberg::tresult _result = Steinberg::Vst::AudioEffect::initialize(context);
        if (_result != Steinberg::kResultOk) {
            return _result;
        }
        _processor = std::make_unique<processor_t>();
        _process_context = std::make_unique<process_context<state_t>>();
        return kResultOk;
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::terminate() SMTG_OVERRIDE
    {
        _processor.reset();
        _process_context.reset();
        return Steinberg::Vst::AudioEffect::terminate();
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::setActive(Steinberg::TBool state) SMTG_OVERRIDE
    {
        _myprocessor.update(_process_ctx);
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE
    {
        _process_ctx._sample_rate = newSetup.sampleRate;
        _myprocessor.update(_process_ctx);
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE
    {
        return Steinberg::kResultTrue;
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE
    {

        _process_ctx._is_transport_playing = data.processContext->kPlaying;
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::setState(Steinberg::IBStream* state) SMTG_OVERRIDE
    {
		IBStreamer _streamer(state, kLittleEndian);
		for (std::size_t _index = 0; _index < _manager.host_visible_count + _manager.host_persistent_count; _index++) {
			parameter_value _value;
			_streamer.readRaw(_value.data(), _value.size());
			_manager.set_from_host(_value);
		}
    }

    template <typename state_t, typename processor_t>
    Steinberg::tresult PLUGIN_API backend_vst3_processor<state_t, processor_t>::getState(Steinberg::IBStream* state) SMTG_OVERRIDE
    {
		_manager.synchronize_from_host();
		IBStreamer _streamer(state, kLittleEndian);
		for (std::size_t _index = 0; _index < _manager.host_visible_count + _manager.host_persistent_count; _index++) {
			const parameter_value& _value = _manager.get_from_host(_index);
			_streamer.writeRaw(_value.data(), _value.size());
		}
    }

#endif
}
}
