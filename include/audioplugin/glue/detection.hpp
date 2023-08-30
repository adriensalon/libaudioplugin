#pragma once

#include <type_traits>

namespace stdx {

// https://en.cppreference.com/w/cpp/experimental/is_detected

// these will no longer be useful with C++20 thanks to concepts (!)

template <typename default_t, typename always_void_t, template <typename...> typename op_t, typename... args_t>
struct detector {
    using value_t = std::false_type;
    using type = default_t;
};

template <typename default_t, template <typename...> typename op_t, typename... args_t>
struct detector<default_t, std::void_t<op_t<args_t...>>, op_t, args_t...> {
    using value_t = std::true_type;
    using type = op_t<args_t...>;
};

struct nonesuch {
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    void operator=(nonesuch const&) = delete;
};

template <template <typename...> typename op_t, typename... args_t>
using is_detected = typename detector<nonesuch, void, op_t, args_t...>::value_t;

template <template <typename...> typename op_t, typename... args_t>
using detected_t = typename detector<nonesuch, void, op_t, args_t...>::type;

template <typename default_t, template <typename...> typename op_t, typename... args_t>
using detected_or = detector<default_t, void, op_t, args_t...>;

template <template <typename...> typename op_t, typename... args_t>
constexpr inline bool is_detected_v = is_detected<op_t, args_t...>::value;

template <typename default_t, template <typename...> typename op_t, typename... args_t>
using detected_or_t = typename detected_or<default_t, op_t, args_t...>::type;

template <typename expected_t, template <typename...> typename op_t, typename... args_t>
using is_detected_exact = std::is_same<expected_t, detected_t<op_t, args_t...>>;

template <typename expected_t, template <typename...> typename op_t, typename... args_t>
constexpr inline bool is_detected_exact_v = is_detected_exact<expected_t, op_t, args_t...>::value;

template <typename to_t, template <typename...> typename op_t, typename... args_t>
using is_detected_convertible = std::is_convertible<detected_t<op_t, args_t...>, to_t>;

template <typename to_t, template <typename...> typename op_t, typename... args_t>
constexpr inline bool is_detected_convertible_v = is_detected_convertible<to_t, op_t, args_t...>::value;
}

#include <public.sdk/source/vst/vstaudioeffect.h>
#include <public.sdk/source/vst/vsteditcontroller.h>

namespace audioplugin {
namespace detail {

    template <typename vst3_component_t>
    using initialize_method = decltype(std::declval<vst3_component_t>().initialize(std::declval<Steinberg::FUnknown*>()));

    template <typename vst3_component_t>
    using terminate_method = decltype(std::declval<vst3_component_t>().terminate());

    template <typename vst3_component_t>
    using get_state_method = decltype(std::declval<vst3_component_t>().getState(std::declval<Steinberg::IBStream*>()));

    template <typename vst3_component_t>
    using set_state_method = decltype(std::declval<vst3_component_t>().setState(std::declval<Steinberg::IBStream*>()));

    template <typename vst3_component_t>
    constexpr inline bool has_initialize_method = stdx::is_detected_exact_v<Steinberg::tresult, initialize_method, vst3_component_t>;

    template <typename vst3_component_t>
    constexpr inline bool has_terminate_method = stdx::is_detected_exact_v<Steinberg::tresult, terminate_method, vst3_component_t>;

    template <typename vst3_component_t>
    constexpr inline bool has_get_state_method = stdx::is_detected_exact_v<Steinberg::tresult, get_state_method, vst3_component_t>;

    template <typename vst3_component_t>
    constexpr inline bool has_set_state_method = stdx::is_detected_exact_v<Steinberg::tresult, set_state_method, vst3_component_t>;

    namespace processor {

        template <typename vst3_processor_t>
        using set_active_method = decltype(std::declval<vst3_processor_t>().setActive(std::declval<Steinberg::TBool>()));

        template <typename vst3_processor_t>
        using setup_processing_method = decltype(std::declval<vst3_processor_t>().setupProcessing(std::declval<Steinberg::Vst::ProcessSetup&>()));

        template <typename vst3_processor_t>
        using can_process_sample_size_method = decltype(std::declval<vst3_processor_t>().canProcessSampleSize(std::declval<Steinberg::int32>()));

        template <typename vst3_processor_t>
        using process_method = decltype(std::declval<vst3_processor_t>().process(std::declval<Steinberg::Vst::ProcessData&>()));

        template <typename vst3_processor_t>
        constexpr inline bool has_set_active_method = stdx::is_detected_exact_v<Steinberg::tresult, set_active_method, vst3_processor_t>;

        template <typename vst3_processor_t>
        constexpr inline bool has_setup_processing_method = stdx::is_detected_exact_v<Steinberg::tresult, setup_processing_method, vst3_processor_t>;

        template <typename vst3_processor_t>
        constexpr inline bool has_can_process_sample_size_method = stdx::is_detected_exact_v<Steinberg::tresult, can_process_sample_size_method, vst3_processor_t>;

        template <typename vst3_processor_t>
        constexpr inline bool has_process_method = stdx::is_detected_exact_v<Steinberg::tresult, process_method, vst3_processor_t>;
    }

    namespace controller {

        template <typename vst3_controller_t>
        using set_component_state_method = decltype(std::declval<vst3_controller_t>().setComponentState(std::declval<Steinberg::IBStream*>()));

        template <typename vst3_controller_t>
        using create_view_method = decltype(std::declval<vst3_controller_t>().createView(std::declval<Steinberg::FIDString>()));

        template <typename vst3_controller_t>
        using set_param_normalized_method = decltype(std::declval<vst3_controller_t>().setParamNormalized(std::declval<Steinberg::Vst::ParamID>(), std::declval<Steinberg::Vst::ParamValue>()));

        template <typename vst3_controller_t>
        using get_param_string_by_value_method = decltype(std::declval<vst3_controller_t>().getParamStringByValue(
            std::declval<Steinberg::Vst::ParamID>(),
            std::declval<Steinberg::Vst::ParamValue>(),
            std::declval<Steinberg::Vst::String128>()));

        template <typename vst3_controller_t>
        using get_param_value_by_string_method = decltype(std::declval<vst3_controller_t>().getParamValueByString(
            std::declval<Steinberg::Vst::ParamID>(),
            std::declval<Steinberg::Vst::TChar*>(),
            std::declval<Steinberg::Vst::ParamValue&>()));

        template <typename vst3_controller_t>
        constexpr inline bool has_set_component_state_method = stdx::is_detected_exact_v<Steinberg::tresult, set_component_state_method, vst3_controller_t>;

        template <typename vst3_controller_t>
        constexpr inline bool has_create_view_method = stdx::is_detected_exact_v<Steinberg::IPlugView*, create_view_method, vst3_controller_t>;

        template <typename vst3_controller_t>
        constexpr inline bool has_set_param_normalized_method = stdx::is_detected_exact_v<Steinberg::tresult, set_param_normalized_method, vst3_controller_t>;

        template <typename vst3_controller_t>
        constexpr inline bool has_get_param_string_by_value_method = stdx::is_detected_exact_v<Steinberg::tresult, get_param_string_by_value_method, vst3_controller_t>;

        template <typename vst3_controller_t>
        constexpr inline bool has_get_param_value_by_string_method = stdx::is_detected_exact_v<Steinberg::tresult, get_param_value_by_string_method, vst3_controller_t>;
    }
}
}