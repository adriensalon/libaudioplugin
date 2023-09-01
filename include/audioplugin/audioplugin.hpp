#pragma once
#include <string>
#include <optional>

#include <audioplugin/core/register.hpp>
#include <audioplugin/core/verify.hpp>
#include <audioplugin/glue/backend.hpp>
#include <audioplugin/glue/frontend.hpp>

/// @brief 
#define REGISTER_OG_PLUGIN(processor_class_m, controller_class_m)             \
    AUDIOPLUGIN_VERIFY_PLUGIN(processor_class_m, controller_class_m)       \
    AUDIOPLUGIN_REGISTER_PLUGIN_AAX()                                      \
    AUDIOPLUGIN_REGISTER_PLUGIN_AU2(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_REGISTER_PLUGIN_AU3(processor_class_m, controller_class_m) \
    AUDIOPLUGIN_REGISTER_PLUGIN_VST2()                                     \
    AUDIOPLUGIN_REGISTER_PLUGIN_VST3(processor_class_m, controller_class_m)

////////

#define REGISTER_UNIVERSAL_PLUGIN(state_t, processor_t, viewer_t) \
	AUDIOPLUGIN_IMPLEMENT_FRONTEND_UNIVERSAL(state_t, processor_t, viewer_t) \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3() \

#define REGISTER_AAX_PLUGIN(plugin_t) \
	AUDIOPLUGIN_IMPLEMENT_FRONTEND_AAX(plugin_t) \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX_PASSTHROUGH(plugin_t) \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3() \

#define REGISTER_AUV2_PLUGIN(processor_t, controller_t)

#define REGISTER_AUV3_PLUGIN(processor_t, controller_t)

#define REGISTER_VST2_PLUGIN(effect_t, editor_t) \
	AUDIOPLUGIN_IMPLEMENT_FRONTEND_VST2(effect_t, editor_t) \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2_PASSTHROUGH(effect_t, editor_t) \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3() \

#define REGISTER_VST3_PLUGIN(processor_t, processor_uid, controller_t, controller_uid) \
	AUDIOPLUGIN_IMPLEMENT_FRONTEND_VST3(processor_t, processor_uid, controller_t, controller_uid) \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AAX() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV2() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_AUV3() \
	AUDIOPLUGIN_IMPLEMENT_BACKEND_VST2(backend_vst2_effect<frontend_vst3_state, frontend_vst3_processor<processor_t, processor_uid>,  frontend_vst3_controller<controller_t, controller_uid>>) 
	// AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3(frontend_vst3_state, backend_vst3_processor<frontend_vst3_processor<processor_t, processor_uid>>) 
	// AUDIOPLUGIN_IMPLEMENT_BACKEND_VST3_PASSTHROUGH(processor_t, processor_uid, controller_t, controller_uid) 