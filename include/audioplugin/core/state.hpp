#pragma once

#include <any>
#include <atomic>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <concurrentqueue.h>

namespace audioplugin {

/// @brief
enum struct host_visibility {
    invisible,
    persistent,
    visible
};

/// @brief
enum struct processor_visibility {
    invisible,
    visible
};

/// @brief
enum struct viewer_visibility {
    invisible,
    visible
};

/// @brief
/// @tparam value_t
/// @tparam visible_from_host_t
template <typename value_t, host_visibility visible_from_host_t = host_visibility::visible>
struct parameter {
    parameter(
        const std::string& name,
        const value_t& value,
        const processor_visibility visible_from_processor = processor_visibility::visible,
        const viewer_visibility visible_from_viewer = viewer_visibility::visible);
};

namespace detail {

    // https://www.kvraudio.com/forum/viewtopic.php?t=390282&sid=84e24d7d1c9e9d23a87d6f124f8ce14a&start=30

    struct parameter_value {

        void* data() const
        {
            return _ptr;
        }

        std::size_t size() const
        {
            return _size;
        }

        template <typename value_t>
        const value_t& get() const
        {
            return std::any_cast<value_t&>(value);
        }

        template <typename value_t>
        void set(const value_t& value)
        {
            value = std::make_any<value_t>(value);
        }

        template <typename value_t>
        void set(value_t&& value)
        {
            value = std::make_any<value_t>(std::move(value));
        }

        // template <typename value_t>
        // static float normalize_32(const std::type_index& type_index, const value_t& value)
        // {
        // }

        // template <typename value_t>
        // static double normalize_64(const std::type_index& type_index, const value_t& value)
        // {
        // }

    private:
        void* _ptr;
        std::size_t _size;
        // std::type_index
    };

    struct parameter_modification {
        std::size_t index;
        parameter_value value;
        // timestamp ?
    };

    struct parameter_controller {
        parameter_value host_value;
        parameter_value processor_value;
        parameter_value viewer_value;
        processor_visibility visible_from_processor;
        viewer_visibility visible_from_viewer;
    };

    struct parameters_manager {

        template <typename value_t>
        void add(
            const std::string& name,
            const value_t& value,
            const host_visibility visible_from_host,
            const processor_visibility visible_from_processor,
            const viewer_visibility visible_from_viewer);

        void build() // build persistent indices
        {
        }

        std::unordered_map<std::string, std::size_t> indices; // so we have std::string keys since the vector will not be modified after build
        std::size_t host_visible_count; // so we know where to push in bulk on setState
        std::size_t host_persistent_count; // so we know where to push in bulk on setState

        void synchronize_from_processor() // pops all needed, updates data and return the modified indices (for eventual frontend call to setParameter)
        {
            parameter_modification _modification;
            while (pipe_to_processor.try_dequeue(_modification)) {
                if (controllers[_modification.index].visible_from_processor != processor_visibility::visible) {
                    throw "received modification that is not supposed to be visible from the processor";
                }
                controllers[_modification.index].processor_value = _modification.value;
            }
        }

        void synchronize_from_viewer(); // pops all needed, updates and return the modified indices (for eventual frontend call)

        void synchronize_from_host() // pops all needed, updates and return the modified indices (for eventual frontend call)
        {
            parameter_modification _modification;
            while (pipe_to_host.try_dequeue(_modification)) {
                if (_modification.index < host_visible_count + host_persistent_count) {
                    throw "received modification that is not supposed to be visible from the host";
                }
                controllers[_modification.index].host_value = _modification.value;
            }
        }

        const parameter_value& get_from_processor(const std::size_t index) const
        {
            return controllers[index].processor_value;
        }

        const parameter_value& get_from_viewer(const std::size_t index) const
        {
            return controllers[index].viewer_value;
        }

        const parameter_value& get_from_host(const std::size_t index) const
        {
            return controllers[index].host_value;
        }

        void set_from_processor(const parameter_modification& modification, const bool persistence_only)
        {
            if (persistence_only && true
                || modification.index < host_visible_count + host_persistent_count) {
                pipe_to_host.enqueue(modification);
            }
            if (controllers[modification.index].visible_from_viewer == viewer_visibility::visible) {
                pipe_to_viewer.enqueue(modification);
            }
        }

        void set_from_viewer(const parameter_modification& modification)
        {
            if (modification.index < host_visible_count + host_persistent_count) {
                pipe_to_host.enqueue(modification);
            }
            if (controllers[modification.index].visible_from_processor == processor_visibility::visible) {
                pipe_to_processor.enqueue(modification);
            }
        }

        void set_from_host(const parameter_modification& modification)
        {
            if (controllers[modification.index].visible_from_viewer == viewer_visibility::visible) {
                pipe_to_viewer.enqueue(modification);
            }
            if (controllers[modification.index].visible_from_processor == processor_visibility::visible) {
                pipe_to_processor.enqueue(modification);
            }
        }

    private:
        moodycamel::ConcurrentQueue<parameter_modification> pipe_to_processor;
        moodycamel::ConcurrentQueue<parameter_modification> pipe_to_viewer;
        moodycamel::ConcurrentQueue<parameter_modification> pipe_to_host;
        std::vector<parameter_controller> controllers;
    };

    // inline parameters_manager _manager = {};

}
}