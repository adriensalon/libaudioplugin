//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace vstsync {
//------------------------------------------------------------------------
static const Steinberg::FUID kwrapperProcessorUID (0xAA2A0417, 0x063258BE, 0xB5FBD442, 0x8AC87FF6);
static const Steinberg::FUID kwrapperControllerUID (0x3C7F1B00, 0x60895F92, 0x98387CFE, 0x73381868);

#define wrapperVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace vstsync
