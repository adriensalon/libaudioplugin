#pragma once

#include <base/source/fstreamer.h>
#include <pluginterfaces/vst/ivstparameterchanges.h>

#include <libplugin/wrapper/vstids.hpp>

namespace libplugin {
namespace detail {

    template <typename processor_t>
    plugin_processor<processor_t>::plugin_processor()
    {
        setControllerClass(plugin_controller_uid);
    }

    template <typename processor_t>
    Steinberg::FUnknown* plugin_processor<processor_t>::createInstance(void* context)
    {
        return reinterpret_cast<Steinberg::Vst::IAudioProcessor*>(new plugin_processor<processor_t>);
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::initialize(FUnknown* context)
    {
        // Here the Plug-in will be instantiated

        //---always initialize the parent-------
        Steinberg::tresult result = AudioEffect::initialize(context);
        // if everything Ok, continue
        if (result != kResultOk) {
            return result;
        }

        //--- create Audio IO ------
        addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
        addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

        /* If you don't need an event bus, you can remove the next line */
        addEventInput(STR16("Event In"), 1);

        return kResultOk;
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::terminate()
    {
        // Here the Plug-in will be de-instantiated, last possibility to remove some memory!

        //---do not forget to call parent ------
        return AudioEffect::terminate();
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::setActive(Steinberg::TBool state)
    {
        //--- called when the Plug-in is enable/disable (On/Off) -----
        return AudioEffect::setActive(state);
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::process(Steinberg::Vst::ProcessData& data)
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

        return kResultOk;
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::setupProcessing(Steinberg::Vst::ProcessSetup& newSetup)
    {
        //--- called before any processing ----
        return AudioEffect::setupProcessing(newSetup);
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::canProcessSampleSize(Steinberg::int32 symbolicSampleSize)
    {
        // by default kSample32 is supported
        if (symbolicSampleSize == Vst::kSample32)
            return kResultTrue;

        // disable the following comment if your processing support kSample64
        /* if (symbolicSampleSize == Vst::kSample64)
                return kResultTrue; */

        return kResultFalse;
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::setState(Steinberg::IBStream* state)
    {
        // called when we load a preset, the model has to be reloaded
        IBStreamer streamer(state, kLittleEndian);

        return kResultOk;
    }

    template <typename processor_t>
    Steinberg::tresult PLUGIN_API plugin_processor<processor_t>::getState(Steinberg::IBStream* state)
    {
        // here we need to save the model
        IBStreamer streamer(state, kLittleEndian);

        return kResultOk;
    }

}
}
