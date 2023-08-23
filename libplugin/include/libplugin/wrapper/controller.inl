#pragma once

#include <public.sdk/source/vst/vsteditcontroller.h>

#include <libplugin/wrapper/vstids.hpp>

namespace libplugin {
namespace detail {

    template <typename controller_t>
    Steinberg::FUnknown* plugin_controller<controller_t>::createInstance(void* context)
    {
        return reinterpret_cast<Steinberg::Vst::IEditController*>(new plugin_controller<controller_t>);
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::initialize(Steinberg::FUnknown* context)
    {
        // Here the Plug-in will be instantiated

        //---do not forget to call parent ------
        Steinberg::tresult result = EditControllerEx1::initialize(context);
        if (result != kResultOk) {
            return result;
        }

        // Here you could register some parameters

        return result;
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::terminate()
    {
        // Here the Plug-in will be de-instantiated, last possibility to remove some memory!

        //---do not forget to call parent ------
        return EditControllerEx1::terminate();
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::setComponentState(Steinberg::IBStream* state)
    {
        // Here you get the state of the component (Processor part)
        if (!state)
            return kResultFalse;

        return kResultOk;
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::setState(Steinberg::IBStream* state)
    {
        // Here you get the state of the controller

        return kResultTrue;
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::getState(Steinberg::IBStream* state)
    {
        // Here you are asked to deliver the state of the controller (if needed)
        // Note: the real state of your plug-in is saved in the processor

        return kResultTrue;
    }

    template <typename controller_t>
    Steinberg::IPlugView* PLUGIN_API plugin_controller<controller_t>::createView(Steinberg::FIDString name)
    {
        // Here the Host wants to open your editor (if you have one)
        if (FIDStringsEqual(name, Vst::ViewType::kEditor)) {
            // create your editor here and return a IPlugView ptr of it
            return nullptr;
        }
        return nullptr;
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::setParamNormalized(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue value)
    {
        // called by host to update your parameters
        Steinberg::tresult result = EditControllerEx1::setParamNormalized(tag, value);
        return result;
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::getParamStringByValue(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue valueNormalized, Steinberg::Vst::String128 string)
    {
        // called by host to get a string for given normalized value of a specific parameter
        // (without having to set the value!)
        return EditControllerEx1::getParamStringByValue(tag, valueNormalized, string);
    }

    template <typename controller_t>
    Steinberg::tresult PLUGIN_API plugin_controller<controller_t>::getParamValueByString(Steinberg::Vst::ParamID tag, Steinberg::Vst::TChar* string, Steinberg::Vst::ParamValue& valueNormalized)
    {
        // called by host to get a normalized value from a string representation of a specific parameter
        // (without having to set the value!)
        return EditControllerEx1::getParamValueByString(tag, string, valueNormalized);
    }

}
}
