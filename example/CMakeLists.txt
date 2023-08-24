project(libplugin_example)

# Here you are supposed to add the libplugin root folder 
# as a subdirectory of your project
# But we alread
# add_subdirectory(external/aaxsdk)
# add_subdirectory(external/auv2sdk)
# add_subdirectory(external/auv3sdk)
# add_subdirectory(external/libplugin)

# Creates a target named ExamplePlugin that we can use as if created by the add_library function.
add_plugin(ExamplePlugin 
	PLUGIN_SOURCES "example.cpp"
	PLUGIN_FX
	PLUGIN_COMPANY "adrien salon"
	PLUGIN_DESCRIPTION "This is an example plugin with no functionnality"
	PLUGIN_VERSION "1.0.0.0"
	PLUGIN_EMAIL "mail@me.com"
	PLUGIN_WEBSITE "mywebsite.com")

# target_include_directories(ExamplePlugin PRIVATE mylib_headers_dir)

# target_link_libraries(ExamplePlugin PRIVATE mylib_target)

# target_compile_definitions(ExamplePlugin PUBLIC DMYDEFINITION=1)

set_target_properties(ExamplePlugin PROPERTIES CXX_STANDARD 17)

