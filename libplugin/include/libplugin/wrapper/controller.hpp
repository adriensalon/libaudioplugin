#pragma once

#include <public.sdk/source/vst/vsteditcontroller.h>

namespace libplugin {
namespace detail {
	
    template <typename controller_t>
    struct plugin_controller : public Steinberg::Vst::EditControllerEx1 {
        plugin_controller() = default;
        plugin_controller(const plugin_controller& other) = default;
        plugin_controller& operator=(const plugin_controller& other) = default;
        plugin_controller(plugin_controller&& other) = default;
        plugin_controller& operator=(plugin_controller&& other) = default;
        ~plugin_controller() SMTG_OVERRIDE = default;

        static Steinberg::FUnknown* createInstance(void* context);

        Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;

        Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API setComponentState(Steinberg::IBStream* state) SMTG_OVERRIDE;
        
		Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API setParamNormalized(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue value) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API getParamStringByValue(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue valueNormalized, Steinberg::Vst::String128 string) SMTG_OVERRIDE;
        
		Steinberg::tresult PLUGIN_API getParamValueByString(Steinberg::Vst::ParamID tag, Steinberg::Vst::TChar* string, Steinberg::Vst::ParamValue& valueNormalized) SMTG_OVERRIDE;

        DEFINE_INTERFACES
        END_DEFINE_INTERFACES(EditController)
        DELEGATE_REFCOUNT(EditController)

    private:
        controller_t _controller_impl = {};
    };
}
}

#include <libplugin/wrapper/controller.inl>