#pragma once

#include <audioplugin/glue/detection.hpp>

/// @brief Macro helper to statically verify a processor and a controller outside of a function.
#define AUDIOPLUGIN_VERIFY_PLUGIN(vst3_processor_m, vst3_controller_m) \
    static_assert(audioplugin::is_plugin_verified<vst3_processor_m, vst3_controller_m>());

namespace audioplugin {

/// @brief Asserts at compile time that the given typename is a valid VST3 component that can be
/// used with the VST3 SDK. This function asserts that the typename provides some general
/// functionnality that a VST3 component should implement.
/// @tparam vst3_component_t is the typename to verify
template <typename vst3_component_t>
constexpr bool is_component_verified()
{
    constexpr bool _is_class = std::is_class_v<vst3_component_t>;
    static_assert(_is_class,
        "Invalid typename for VST3 component. Likely the given typename does not refer ti an "
        "existing type. Please provide a valid one.");

    constexpr bool _is_polymorphic = std::is_polymorphic_v<vst3_component_t>;
    static_assert(_is_polymorphic,
        "The given component is not polymorphic. VST3 components work by inheriting interfaces "
        "and overriding some appropriate methods.");

	if constexpr(!std::is_final_v<vst3_component_t>) {
		constexpr bool _has_virtual_destructor = std::has_virtual_destructor_v<vst3_component_t>;
		static_assert(_has_virtual_destructor,
			"The given component is not final but does not have a virtual destructor.");
	}
	
    constexpr bool _is_component = std::is_base_of_v<Steinberg::Vst::ComponentBase, vst3_component_t>;
    static_assert(_is_component,
        "The given component does not inherit the Steinberg::Vst::ComponentBase interface. This "
        "is required for VST3 processors, controllers, and single components.");

    constexpr bool _has_initialize = detail::has_initialize_method<vst3_component_t>;
    static_assert(_has_initialize,
        "The given component does not implement the initialize method. This is required for all "
		"VST3 components.");

    constexpr bool _has_terminate = detail::has_terminate_method<vst3_component_t>;
    static_assert(_has_terminate,
        "The given component does not implement the terminate method. This is required for all "
		"VST3 components.");

    constexpr bool _has_get_state = detail::has_get_state_method<vst3_component_t>;
    static_assert(_has_get_state,
        "The given component does not implement the getState method. This is required for all "
		"VST3 components.");

    constexpr bool _has_set_state = detail::has_set_state_method<vst3_component_t>;
    static_assert(_has_set_state,
        "The given component does not implement the setState method. This is required for all "
		"VST3 components.");

    return true;
}

/// @brief Asserts at compile time that the given typenames are valid VST3 processor and controller
/// that can be used with the VST3 SDK. This function asserts that the typename provides some 
/// general functionnality that VST3 processor and controller should implement.
/// @tparam vst3_processor_t is the processor typename to verify
/// @tparam vst3_controller_t is the controller typename to verify
template <typename vst3_processor_t, typename vst3_controller_t>
constexpr bool is_plugin_verified()
{
    is_component_verified<vst3_processor_t>();
    is_component_verified<vst3_controller_t>();

    constexpr bool _is_processor = std::is_base_of_v<Steinberg::Vst::AudioEffect, vst3_processor_t>;
    static_assert(_is_processor,
        "The given processor does not inherit the Steinberg::Vst::AudioEffect interface. This "
        "is required for VST3 processors.");

    constexpr bool _is_controller = std::is_base_of_v<Steinberg::Vst::EditControllerEx1, vst3_controller_t>;
    static_assert(_is_controller,
        "The given controller does not inherit the Steinberg::Vst::EditControllerEx1 interface. "
        "This is required for VST3 controllers.");

    constexpr bool _has_processor_set_active = detail::processor::has_set_active_method<vst3_processor_t>;
    static_assert(_has_processor_set_active,
        "The given component does not implement the setActive method. This is required for all "
		"VST3 processors.");

    constexpr bool _has_processor_setup_processing = detail::processor::has_setup_processing_method<vst3_processor_t>;
    static_assert(_has_processor_setup_processing,
        "The given component does not implement the setupProcessing method. This is required for "
		"all VST3 processors.");

    constexpr bool _has_processor_can_process_sample_size = detail::processor::has_can_process_sample_size_method<vst3_processor_t>;
    static_assert(_has_processor_can_process_sample_size,
        "The given component does not implement the canProcessSampleSize method. This is required "
		"for all VST3 processors.");

    constexpr bool _has_process = detail::processor::has_process_method<vst3_processor_t>;
    static_assert(_has_process,
        "The given component does not implement the process method. This is required for all VST3 "
		"processors.");

    constexpr bool _has_set_component_state = detail::controller::has_set_component_state_method<vst3_controller_t>;
    static_assert(_has_set_component_state,
        "The given component does not implement the setComponentState method. This is required for "
		"all VST3 controllers.");

    constexpr bool _has_create_view = detail::controller::has_create_view_method<vst3_controller_t>;
    static_assert(_has_create_view,
        "The given component does not implement the createView method. This is required for all "
		"VST3 controllers.");

    constexpr bool _has_set_param_normalized = detail::controller::has_set_param_normalized_method<vst3_controller_t>;
    static_assert(_has_set_param_normalized,
        "The given component does not implement the setParamNormalized method. This is required "
		"for all VST3 controllers.");

    constexpr bool _has_get_param_string_by_value = detail::controller::has_get_param_string_by_value_method<vst3_controller_t>;
    static_assert(_has_get_param_string_by_value,
        "The given component does not implement the getParamStringByValue method. This is required "
		"for all VST3 controllers.");

    constexpr bool _has_get_param_value_by_string = detail::controller::has_get_param_value_by_string_method<vst3_controller_t>;
    static_assert(_has_get_param_value_by_string,
        "The given component does not implement the getParamValueByString method. This is required "
		"for all VST3 controllers.");

    return true;
}

}