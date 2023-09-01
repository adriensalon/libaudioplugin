#pragma once

#include <functional>

namespace audioplugin {

/// @brief
/// @tparam state_t
template <typename state_t>
struct view_context {

    double read_parameter(const std::string& name) const;

    void write_parameter(const std::string& name, const double value);

    void read_state_unsafe(const std::function<void(const state_t&)>& callback) const;

    void write_state_unsafe(const std::function<void(const state_t&)>& callback) const;

    void* native_window() const;
};
}