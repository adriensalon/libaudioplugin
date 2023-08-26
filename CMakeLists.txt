cmake_minimum_required(VERSION 3.14.0)

project(libaudioplugin_all)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")
include(PluginBuild)
include(PluginConfigure)
include(PluginDeploy)
include(PluginParse)

option(LIBAUDIOPLUGIN_BUILD_DOC "Build Doxygen documentation" ON)
option(LIBAUDIOPLUGIN_BUILD_EXAMPLE "Build example executable" ON)

plugin_parse_platform(_platform) # available backends
plugin_parse_backend(_backend) # ca va dans la fonctrion

message("-- [libaudioplugin] Configuring for ${_platform} platform")
message("-- [libaudioplugin] Configuring for ${_backend} backends")  # available backends
message("-- [libaudioplugin] Building Doxygen documentation is ${LIBAUDIOPLUGIN_BUILD_DOC}")
message("-- [libaudioplugin] Building example plugin is ${LIBAUDIOPLUGIN_BUILD_EXAMPLE}")

plugin_configure_sdk(
	${_backend}  # available backends
	${_platform}
	${CMAKE_CURRENT_LIST_DIR}/external/ausdk
	${CMAKE_CURRENT_LIST_DIR}/external/aaxsdk
	${CMAKE_CURRENT_LIST_DIR}/external/vst2sdk
	${CMAKE_CURRENT_LIST_DIR}/external/vst3sdk)

# @brief This is the main CMake function exported by this library
# @param target
# @param VALIDATE
# @param FX
# @param INSTRUMENT
# @param NAME <name>
# @param COMPANY <company>
# @param DESCRIPTION <description>
# @param VERSION <version>
# @param EMAIL <email>
# @param WEBSITE <website>
# @param BACKEND <backend>
function(add_plugin target)
	set(_add_plugin_options VALIDATE FX INSTRUMENT)
	set(_add_plugin_args COMPANY DESCRIPTION VERSION EMAIL WEBSITE BACKEND)
	set(_add_plugin_multi SOURCES)
	cmake_parse_arguments(PARSE_ARGV 1 PLUGIN "${_add_plugin_options}" "${_add_plugin_args}" "${_add_plugin_multi}")
	
	plugin_parse_type(${PLUGIN_INSTRUMENT} ${PLUGIN_FX}	_plugin_type)
	plugin_parse_company(PLUGIN_COMPANY _plugin_company)
	plugin_parse_description(PLUGIN_DESCRIPTION _plugin_description)
	plugin_parse_version(PLUGIN_VERSION _plugin_version)
	plugin_parse_email(PLUGIN_EMAIL _plugin_email)
	plugin_parse_website(PLUGIN_WEBSITE _plugin_website)
	# parse sources ?

	message("-- [libaudioplugin] Plugin name is '${target}'")
	message("-- [libaudioplugin] Plugin category is '${_plugin_type}'")
	message("-- [libaudioplugin] Plugin company is '${_plugin_company}'")
	message("-- [libaudioplugin] Plugin description is '${_plugin_description}'")
	message("-- [libaudioplugin] Plugin version is '${_plugin_version}'")
	message("-- [libaudioplugin] Plugin email is '${_plugin_email}'")
	message("-- [libaudioplugin] Plugin website is '${_plugin_website}'")

	project(
		${target}
		VERSION ${_plugin_version}
		DESCRIPTION ${_plugin_description})

	plugin_add_target(
		${target}
		${_plugin_company}
		${_backend}
		${PLUGIN_SOURCES}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk)

	plugin_include_directories(
		${target}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include)

	plugin_sources(
		${target}
		${_backend}
		${_platform}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk)

	plugin_link_libraries(
		${target}
		${_backend}
		${_platform}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk)

	plugin_compile_definitions(
		${target}
		${_backend}
		${_plugin_type}
		${_plugin_company}
		${_plugin_description}
		${_plugin_version}
		${_plugin_email}
		${_plugin_website})

	plugin_bundle()

	plugin_validate(
		${target}
		${_backend}
		${PLUGIN_VALIDATE})

	plugin_clean(
		${target}
		${_backend})

endfunction()

if(LIBAUDIOPLUGIN_BUILD_DOC)
	add_subdirectory(doc)
endif()

if(LIBAUDIOPLUGIN_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()
