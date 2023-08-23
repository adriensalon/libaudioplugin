project(libplugin_test)

add_library(libplugin_test STATIC "source/test.cpp")

add_plugin(libplugin_test
	PLUGIN_NAME "TestPlugin"
	PLUGIN_COMPANY "adrien salon"
	PLUGIN_DESCRIPTION "This is the testing plugin"
	PLUGIN_VERSION "1.0.0.0")