project(libplugin_demo)

add_library(libplugin_demo STATIC "source/demo.cpp")

add_plugin(libplugin_demo
	PLUGIN_NAME "DemoPlugin"
	PLUGIN_COMPANY "adrien salon"
	PLUGIN_DESCRIPTION "This is an example demo plugin"
	PLUGIN_VERSION "1.0.0.0")