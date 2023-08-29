project(libaudioplugin_example)

# Here you are supposed to add the libaudioplugin root folder 
# as a subdirectory of your project
# But we alread
# add_subdirectory(external/aaxsdk)
# add_subdirectory(external/auv2sdk)
# add_subdirectory(external/auv3sdk)
# add_subdirectory(external/libaudioplugin)

# Creates a target named ExamplePlugin that we can use as if created by the add_library function.
# add_plugin(TestPlug
# 	BACKEND "VST3" # We comment this for CI so we can use the preferred backend
# 	VALIDATE
# 	SOURCES 
# 		"source/version.h"
# 		"source/myplugincids.h"
# 		"source/myplugincontroller.h"
# 		"source/myplugincontroller.cpp"
# 		"source/mypluginentry.cpp"
# 		"source/mypluginprocessor.h"
# 		"source/mypluginprocessor.cpp"
# 	FX
# 	COMPANY "adrien salon"
# 	DESCRIPTION "An example plugin"
# 	VERSION "1.0.0.0"
# 	EMAIL "mail@me.com"
# 	WEBSITE "mywebsite.com")
	

# target_include_directories(ExamplePlugin PRIVATE mylib_headers_dir)

# target_link_libraries(ExamplePlugin PRIVATE mylib_target)

# target_compile_definitions(ExamplePlugin PUBLIC DMYDEFINITION=1)

#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#

# project(TestPlug
#     # This is your plug-in version number. Change it here only.
#     # Version number symbols usable in C++ can be found in
#     # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
#     VERSION 1.0.0.0 
#     DESCRIPTION "TestPlug VST 3 Plug-in"
# )

# smtg_add_vst3plugin(TestPlug
#     source/version.h
#     source/myplugincids.h
#     source/mypluginprocessor.h
#     source/mypluginprocessor.cpp
#     source/myplugincontroller.h
#     source/myplugincontroller.cpp
#     source/mypluginentry.cpp
# )

# target_link_libraries(TestPlug
#     PRIVATE
#         sdk
# )

# smtg_target_configure_version_file(TestPlug)

# target_sources(TestPlug PRIVATE 
# 	resource/win32resource.rc
# )


add_plugin(ExamplePlugin
	BACKEND "VST2" # We comment this for CI so we can use the preferred backend
	VALIDATE
	SOURCES 
		source/myplugincontroller.h
		source/myplugincontroller.cpp
		source/mypluginentry.cpp
		source/mypluginprocessor.h
		source/mypluginprocessor.cpp
	FX
	COMPANY "adrien salon"
	DESCRIPTION "An example plugin"
	VERSION "1.0.0.0"
	EMAIL "mail@me.com"
	WEBSITE "mywebsite.com")