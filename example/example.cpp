#include <libplugin/libplugin.hpp>

#include <public.sdk/source/vst/vstaudioeffect.h>
#include <public.sdk/source/vst/vsteditcontroller.h>

#include <pluginterfaces/vst/ivstparameterchanges.h>

#include <base/source/fstreamer.h>

struct vst3_processor final : public Steinberg::Vst::AudioEffect {

	vst3_processor()
	{
        setControllerClass(PLUGIN_CONTROLLER_UID);
    }

	~vst3_processor() override
	{
		
	}

	static Steinberg::FUnknown* createInstance(void* context)
	{
        return reinterpret_cast<Steinberg::Vst::IAudioProcessor*>(new vst3_processor);
    }

	Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override
	{
        // Here the Plug-in will be instantiated

        //---always initialize the parent-------
        Steinberg::tresult result = AudioEffect::initialize(context);
        // if everything Ok, continue
        if (result != Steinberg::kResultOk) {
            return result;
        }

        //--- create Audio IO ------
        addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
        addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

        /* If you don't need an event bus, you can remove the next line */
        addEventInput(STR16("Event In"), 1);

        return Steinberg::kResultOk;
    }
	
	Steinberg::tresult PLUGIN_API terminate() override
	{
		// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

        //---do not forget to call parent ------
        return AudioEffect::terminate();
	}
	
	Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) override
	{
		// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

        //---do not forget to call parent ------
        return AudioEffect::terminate();
	}
	
	Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) override
	{
		//--- called before any processing ----
        return AudioEffect::setupProcessing(newSetup);
	}
	
	Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) override
	{
		// by default kSample32 is supported
        if (symbolicSampleSize == Steinberg::Vst::kSample32)
            return Steinberg::kResultTrue;

        // disable the following comment if your processing support kSample64
        /* if (symbolicSampleSize == Vst::kSample64)
                return kResultTrue; */

        return Steinberg::kResultFalse;
	}
	
	Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) override
	{
		//--- First : Read inputs parameter changes-----------

        /*if (data.inputParameterChanges)
        {
            int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
            for (int32 index = 0; index < numParamsChanged; index++)
            {
                if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
                {
                    Vst::ParamValue value;
                    int32 sampleOffset;
                    int32 numPoints = paramQueue->getPointCount ();
                    switch (paramQueue->getParameterId ())
                    {
                                    }
                            }
                    }
            }*/

        //--- Here you have to implement your processing

        return Steinberg::kResultOk;
	}
	
	Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) override
	{
		// called when we load a preset, the model has to be reloaded
        Steinberg::IBStreamer streamer(state, kLittleEndian);

        return Steinberg::kResultOk;
	}
	
	Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) override
	{
		// here we need to save the model
        Steinberg::IBStreamer streamer(state, kLittleEndian);

        return Steinberg::kResultOk;
	}	
};

struct vst3_controller final : public Steinberg::Vst::EditControllerEx1 {

    static Steinberg::FUnknown* createInstance(void* context)
	{
		return reinterpret_cast<Steinberg::Vst::IEditController*>(new vst3_controller);
	}

    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override
	{
		// Here the Plug-in will be instantiated

        //---do not forget to call parent ------
        Steinberg::tresult result = EditControllerEx1::initialize(context);
        if (result != Steinberg::kResultOk) {
            return result;
        }
        // Here you could register some parameters

        return result;
	}

    Steinberg::tresult PLUGIN_API terminate() override
	{
		// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

        //---do not forget to call parent ------
        return EditControllerEx1::terminate();
	}

    Steinberg::tresult PLUGIN_API setComponentState(Steinberg::IBStream* state) override
	{
		// Here you get the state of the component (Processor part)
        if (!state)
            return Steinberg::kResultFalse;

        return Steinberg::kResultOk;
	}

    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name) override
	{
		// Here the Host wants to open your editor (if you have one)
        if (Steinberg::FIDStringsEqual(name, Steinberg::Vst::ViewType::kEditor)) {
            // create your editor here and return a IPlugView ptr of it
            return nullptr;
        }
        return nullptr;		
	}

    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) override
	{
		// Here you are asked to deliver the state of the controller (if needed)
        // Note: the real state of your plug-in is saved in the processor

        return Steinberg::kResultTrue;
	}

    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) override
	{		
		// Here you get the state of the controller

        return Steinberg::kResultTrue;
	}

    Steinberg::tresult PLUGIN_API setParamNormalized(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue value) override
	{
		// called by host to update your parameters
        Steinberg::tresult result = EditControllerEx1::setParamNormalized(tag, value);
        return result;
	}

    Steinberg::tresult PLUGIN_API getParamStringByValue(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue valueNormalized, Steinberg::Vst::String128 string) override
	{
		// called by host to get a string for given normalized value of a specific parameter
        // (without having to set the value!)
        return Steinberg::Vst::EditControllerEx1::getParamStringByValue(tag, valueNormalized, string);
	}

    Steinberg::tresult PLUGIN_API getParamValueByString(Steinberg::Vst::ParamID tag, Steinberg::Vst::TChar* string, Steinberg::Vst::ParamValue& valueNormalized) override
	{
		// called by host to get a normalized value from a string representation of a specific parameter
        // (without having to set the value!)
        return Steinberg::Vst::EditControllerEx1::getParamValueByString(tag, string, valueNormalized);
	}

    Steinberg::tresult PLUGIN_API queryInterface(const Steinberg::TUID iid, void** obj) override 
	{ 
		return Steinberg::Vst::EditController::queryInterface(iid, obj); 
	}

    Steinberg::uint32 PLUGIN_API addRef() override 
	{ 
		return Steinberg::Vst::EditController::addRef(); 
	}

    Steinberg::uint32 PLUGIN_API release() override 
	{ 
		return Steinberg::Vst::EditController::release(); 
	}
};

REGISTER_PLUGIN(vst3_processor, vst3_controller)