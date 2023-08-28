//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace vstsync {
//------------------------------------------------------------------------
static const Steinberg::FUID kTestPlugProcessorUID (0x248342CF, 0x44A05642, 0xB8DE531F, 0x3A74690F);
static const Steinberg::FUID kTestPlugControllerUID (0x6A94D5D3, 0x1842569C, 0xAB2BCCF2, 0x5F9B2599);

#define TestPlugVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace vstsync
