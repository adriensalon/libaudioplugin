project(libplugin_test)

add_plugin(TestPlugin
	PLUGIN_SOURCES "source/test.cpp"
	PLUGIN_INSTRUMENT
	PLUGIN_NAME "TestPlugin"
	PLUGIN_COMPANY "adrien salon"
	PLUGIN_DESCRIPTION "This is the testing plugin"
	PLUGIN_VERSION "1.0.0.0")