#pragma once

#if defined(AUDIOPLUGIN_BACKEND_VST3)
#include <public.sdk/source/vst/vstaudioeffect.h>
#include <public.sdk/source/vst/vsteditcontroller.h>
#endif

#include <audioplugin/core/process.hpp>
#include <audioplugin/core/state.hpp>
#include <audioplugin/core/view.hpp>

#define AUDIOPLUGIN_IMPLEMENT_FRONTEND_AAX()
#define AUDIOPLUGIN_IMPLEMENT_FRONTEND_AUV2()
#define AUDIOPLUGIN_IMPLEMENT_FRONTEND_AUV3()
#define AUDIOPLUGIN_IMPLEMENT_FRONTEND_VST2()
#define AUDIOPLUGIN_IMPLEMENT_FRONTEND_VST3(processor_t, processor_uid, controller_t, controller_uid)

namespace audioplugin {
namespace detail {

#if defined(AUDIOPLUGIN_FRONTEND_VST3)

    struct frontend_vst3_state {
		
    };

	template <typename vst3_processor_t>
    struct frontend_vst3_processor {		
		void update(process_context<frontend_vst3_state>& context);
	
	private:
		vst3_processor_t _processor;
    };

    struct frontend_vst3_view {
		void update(view_context<frontend_vst3_state>& context);		
    };

#endif
}
}

