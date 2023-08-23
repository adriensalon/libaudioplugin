project(libplugin_demo)

add_plugin(DemoPlugin 
	PLUGIN_SOURCES "source/demo.cpp"
	PLUGIN_FX
	PLUGIN_COMPANY "adrien salon"
	PLUGIN_DESCRIPTION "This is an example demo plugin"
	PLUGIN_VERSION "1.0.0.0")

set(OKOK ON)
target_compile_definitions(DemoPlugin PUBLIC OKOK)