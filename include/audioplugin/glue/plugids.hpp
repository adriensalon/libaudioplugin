#pragma once

#include <pluginterfaces/base/fplatform.h>

/// @brief
#if !defined(AUDIOPLUGIN_PROCESSOR_UID)
#define AUDIOPLUGIN_PROCESSOR_UID audioplugin::detail::processor_uid
#endif

/// @brief
#if !defined(AUDIOPLUGIN_CONTROLLER_UID)
#define AUDIOPLUGIN_CONTROLLER_UID audioplugin::detail::controller_uid
#endif

namespace audioplugin {
namespace detail {

    static const Steinberg::FUID processor_uid(0xAA2A0417, 0x063258BE, 0xB5FBD442, 0x8AC87FF6);
    static const Steinberg::FUID controller_uid(0x3C7F1B00, 0x60895F92, 0x98387CFE, 0x73381868);
}
}