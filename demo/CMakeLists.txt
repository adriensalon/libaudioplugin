project(libplugin_demo)

add_library(libplugin_demo STATIC "source/demo.cpp")

target_link_libraries(libplugin_demo libplugin)

add_plugin(libplugin_demo 
	PLUGIN_FX
	PLUGIN_NAME "DemoPlugin"
	PLUGIN_COMPANY "adrien salon"
	PLUGIN_DESCRIPTION "This is an example demo plugin"
	PLUGIN_VERSION "1.0.0.0")