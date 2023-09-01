#pragma once

#include <functional>
#include <optional>
#include <vector>

#include <audioplugin/core/state.hpp>

namespace audioplugin {

/// @brief
/// @tparam state_t
template <typename state_t>
struct process_context {

	template <typename value_t>
	const value_t& get_parameter(const std::size_t index)
	{
		_manager.synchronize_from_processor();
		return _manager.get_from_processor(index);
	}

	template <typename value_t>
	const value_t& get_parameter(const std::string& name)
	{
		_manager.synchronize_from_processor();
		return _manager.get_from_processor(_manager.indices[name]);
	}

    void send_midi_message();

    // const std::optional<info_request> info;

    /// @brief
    bool is_bypassed() const;

    /// @brief
    bool is_rendering_offline() const;

    /// @brief
    std::optional<int> state_change() const;

    /// @brief
    std::vector<float>& samples32_to_replace();

    /// @brief
    std::vector<double>& samples64_to_replace();

    /// @brief
    const std::vector<void*>& midi_messages();

    /// @brief
    double sample_rate() const;

    /// @brief
    unsigned int latency_samples() const;

    /// @brief
    unsigned int tail_samples() const;

    /// @brief
    double position_samples() const;

    /// @brief
    double position_ppq() const;

    /// @brief
    double tempo_bpm() const;

    /// @brief
    bool is_transport_running() const;

    /// @brief
    double samples_per_beat() const;

    /// @brief
    std::pair<unsigned int, unsigned int> time_signature() const;

private:
    bool _is_transport_playing = false;
    double _sample_rate = 0.0;
    friend struct backend_vst3_processor;
};
}