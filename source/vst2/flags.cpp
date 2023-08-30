#if defined(AUDIOPLUGIN_BACKEND_VST2)

#include <vst2/env.hpp>

extern std::unique_ptr<audioplugin::validate::plugin_data> plugin;

TEST(AUDIOPLUGIN_TEST_SUITE, VST2FlagsProgramChunk)
{	
	EXPECT_TRUE(plugin->is_loaded() && 
		plugin->data->flags & VstAEffectFlags::effFlagsProgramChunks);
}

TEST(AUDIOPLUGIN_TEST_SUITE, VST2FlagsNoSoundInStop)
{
	EXPECT_TRUE(plugin->is_loaded() && 
		plugin->data->flags & VstAEffectFlags::effFlagsNoSoundInStop);
}

TEST(AUDIOPLUGIN_TEST_SUITE, VST2FlagsCanReplacing)
{
	EXPECT_TRUE(plugin->is_loaded() && 
		plugin->data->flags & VstAEffectFlags::effFlagsCanReplacing);
}

#endif