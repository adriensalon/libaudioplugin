#pragma once

#include <memory>

#if defined(AUDIOPLUGIN_BACKEND_VST2)
#include <public.sdk/source/vst2.x/audioeffectx.h>
#elif defined(AUDIOPLUGIN_BACKEND_VST3)
#include <public.sdk/source/vst/vstaudioeffect.h>
#include <public.sdk/source/vst/vsteditcontroller.h>
#endif

#include <audioplugin/core/process.hpp>
#include <audioplugin/core/state.hpp>
#include <audioplugin/core/view.hpp>

#if defined(AUDIOPLUGIN_BACKEND_AAX)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX_PASSTHROUGH()
#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX_PASSTHROUGH()
#endif

#if defined(AUDIOPLUGIN_BACKEND_AUV2)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2_PASSTHROUGH()
#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2_PASSTHROUGH()
#endif

#if defined(AUDIOPLUGIN_BACKEND_AUV3)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3_PASSTHROUGH()
#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3_PASSTHROUGH()
#endif

#if defined(AUDIOPLUGIN_BACKEND_VST2)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2(state_t, processor_t, viewer_t)        \
    AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2_ENTRY(                                     \
        audioplugin::detail::backend_vst2_effect<state_t, processor_t, viewer_t>)                          
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2_PASSTHROUGH()
#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2()
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2_PASSTHROUGH()
#endif

#if defined(AUDIOPLUGIN_BACKEND_VST3)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3(state_t, processor_t, viewer_t) \
    AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_ENTRY(                              \
        audioplugin::detail::backend_vst3_processor<state_t, processor_t>, \
        audioplugin::detail::backend_vst3_processor_uid,                   \
        audioplugin::detail::backend_vst3_controller<state_t, viewer_t>,   \
        audioplugin::detail::backend_vst3_controller_uid)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_PASSTHROUGH(processor_t, processor_uid, controller_t, controller_uid) \
    AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_ENTRY(processor_t, processor_uid, controller_t, controller_uid)
#else
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3(state_t, processor_t, viewer_t)
#define AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_PASSTHROUGH(processor_t, processor_uid, controller_t, controller_uid)
#endif

namespace audioplugin {
namespace detail {

#if defined(AUDIOPLUGIN_BACKEND_VST2)

    inline const Steinberg::FUID backend_vst2_effect_uid(0xAA2A0417, 0x063258BE, 0xB5FBD442, 0x8AC87FF6);

    template <typename state_t, typename processor_t, typename viewer_t>
    struct backend_vst2_effect final : public AudioEffectX {
        backend_vst2_effect(audioMasterCallback audioMaster);
        ~backend_vst2_effect();

        virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) override;
        virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) override;
        virtual void setProgramName(char* name) override;
        virtual void getProgramName(char* name) override;
        virtual void setParameter(VstInt32 index, float value) override;
        virtual float getParameter(VstInt32 index) override;
        virtual void getParameterLabel(VstInt32 index, char* label) override;
        virtual void getParameterDisplay(VstInt32 index, char* text) override;
        virtual void getParameterName(VstInt32 index, char* text) override;
        virtual bool getEffectName(char* name) override;
        virtual bool getVendorString(char* text) override;
        virtual bool getProductString(char* text) override;
        virtual VstInt32 getVendorVersion() override;

    private:
        std::unique_ptr<state_t> _state = nullptr;
        std::unique_ptr<processor_t> _processor = nullptr;
        std::unique_ptr<viewer_t> _viewer = nullptr;
        std::unique_ptr<process_context<state_t>> _process_context = nullptr;
        std::unique_ptr<view_context<state_t>> _view_context = nullptr;
    };

#elif defined(AUDIOPLUGIN_BACKEND_VST3)

    inline const Steinberg::FUID backend_vst3_processor_uid(0xAA2A0417, 0x063258BE, 0xB5FBD442, 0x8AC87FF6);

    template <typename state_t, typename processor_t>
    struct backend_vst3_processor final : public Steinberg::Vst::AudioEffect {
        backend_vst3_processor();
        ~backend_vst3_processor() SMTG_OVERRIDE;

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
        std::unique_ptr<state_t> _state = nullptr;
        std::unique_ptr<processor_t> _processor = nullptr;
        std::unique_ptr<process_context<state_t>> _process_context = nullptr;
    };

    inline const Steinberg::FUID backend_vst3_controller_uid(0x3C7F1B00, 0x60895F92, 0x98387CFE, 0x73381868);

    template <typename state_t, typename viewer_t>
    struct backend_vst3_controller final : public Steinberg::Vst::EditControllerEx1 {
        backend_vst3_controller() = default;
        ~backend_vst3_controller() SMTG_OVERRIDE = default;

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
        viewer_t _viewer;
        view_context<state_t> _view_context;
    };

#endif
}
}

#include <audioplugin/glue/backend.inl>