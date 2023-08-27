project(libaudioplugin_example)

# Here you are supposed to add the libaudioplugin root folder 
# as a subdirectory of your project
# But we alread
# add_subdirectory(external/aaxsdk)
# add_subdirectory(external/auv2sdk)
# add_subdirectory(external/auv3sdk)
# add_subdirectory(external/libaudioplugin)

# Creates a target named ExamplePlugin that we can use as if created by the add_library function.
add_plugin(ExamplePlugin 
	# BACKEND "VST2" # We comment this for CI so we can use the preferred backend
	VALIDATE
	SOURCES "example.cpp"
	FX
	COMPANY "adrien salon"
	DESCRIPTION "This is an example plugin with no functionnality"
	VERSION "1.0.0.0"
	EMAIL "mail@me.com"
	WEBSITE "mywebsite.com")
	

# target_include_directories(ExamplePlugin PRIVATE mylib_headers_dir)

# target_link_libraries(ExamplePlugin PRIVATE mylib_target)

# target_compile_definitions(ExamplePlugin PUBLIC DMYDEFINITION=1)

