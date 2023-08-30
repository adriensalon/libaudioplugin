
#include <gtest/gtest.h>

#if defined(AUDIOPLUGIN_BACKEND_VST2)

TEST(AUDIOPLUGIN_TEST_SUITE, VST2Test1)
{
    EXPECT_STREQ("ok", "ok");
}

TEST(AUDIOPLUGIN_TEST_SUITE, VST2Test2)
{
    EXPECT_STREQ("ok", "ok");
}

#endif