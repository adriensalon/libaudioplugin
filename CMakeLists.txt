cmake_minimum_required(VERSION 3.14.0)

project(libaudioplugin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(PluginBuild)
include(PluginConfigure)
include(PluginDeploy)
include(PluginFetch)
include(PluginParse)

# build optionals
option(LIBAUDIOPLUGIN_BUILD_DOC "Build Doxygen documentation" ON)
option(LIBAUDIOPLUGIN_BUILD_EXAMPLE "Build example executable" ON)

# paths to the AAX SDK (defaults to /external/aaxsdk, change if needed for other projects not including libaudioplugin ?)
set(LIBAUDIOPLUGIN_AAXSDK_PATH "${CMAKE_CURRENT_LIST_DIR}/external/aaxsdk" CACHE STRING "Default path for the AAX SDK (get there 'http://developer.avid.com/aax/')")
set(LIBAUDIOPLUGIN_COREAUDIOSDK_PATH "${CMAKE_CURRENT_LIST_DIR}/external/ausdk" CACHE STRING "Default path for the CoreAudio SDK (get there 'https://developer.apple.com/library/archive/samplecode/CoreAudioUtilityClasses/Introduction/Intro.html')")

plugin_detect_backend(_platform _available_backends)

plugin_fetch_sdk(
	"${_available_backends}"
	${LIBAUDIOPLUGIN_AAXSDK_PATH}
	${LIBAUDIOPLUGIN_COREAUDIOSDK_PATH})

plugin_configure_sdk(
	"${_available_backends}"
	${_platform}
	${LIBAUDIOPLUGIN_AAXSDK_PATH}
	${LIBAUDIOPLUGIN_COREAUDIOSDK_PATH}
	${CMAKE_CURRENT_LIST_DIR}/external/vst2sdk
	${CMAKE_CURRENT_LIST_DIR}/external/vst3sdk)

plugin_configure_validator(
	${CMAKE_CURRENT_LIST_DIR}/external
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/source)
	
# your project scope preferred backend variable)
set(LIBAUDIOPLUGIN_PREFERRED_BACKEND "VST3" CACHE STRING "Selected plugin backend")
set_property(CACHE LIBAUDIOPLUGIN_PREFERRED_BACKEND PROPERTY STRINGS ${_available_backends})

message("-- [libaudioplugin] Configuring for ${_platform} platform")
message("-- [libaudioplugin] Available backends are ${_available_backends}")
message("-- [libaudioplugin] Preferred backend is ${LIBAUDIOPLUGIN_PREFERRED_BACKEND}")
message("-- [libaudioplugin] Building documentation is ${LIBAUDIOPLUGIN_BUILD_DOC}")
message("-- [libaudioplugin] Building example plugin is ${LIBAUDIOPLUGIN_BUILD_EXAMPLE}")

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
	
	plugin_parse_backend(
		${LIBAUDIOPLUGIN_PREFERRED_BACKEND}
		PLUGIN_BACKEND
		_backend)

	plugin_parse_type(
		${PLUGIN_INSTRUMENT}
		${PLUGIN_FX}
		_type)

	plugin_parse_company(PLUGIN_COMPANY _company)
	plugin_parse_description(PLUGIN_DESCRIPTION _description)
	plugin_parse_version(PLUGIN_VERSION _version)
	plugin_parse_email(PLUGIN_EMAIL _email)
	plugin_parse_website(PLUGIN_WEBSITE _website)

	message("-- [libaudioplugin] Building ${_backend} plugin ${target}")
	message("-- [libaudioplugin] Plugin category is ${_type}")
	message("-- [libaudioplugin] Plugin company is ${_company}")
	message("-- [libaudioplugin] Plugin description is ${_description}")
	message("-- [libaudioplugin] Plugin version is ${_version}")
	message("-- [libaudioplugin] Plugin email is ${_email}")
	message("-- [libaudioplugin] Plugin website is ${_website}")

	project(${target} VERSION ${_version} DESCRIPTION ${_description})

	plugin_configure_target(
		"${PLUGIN_SOURCES}"
		${target}
		${_company}
		${_backend}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk)

	plugin_include_directories(
		${target}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include)

	plugin_sources(
		${target}
		${_backend}
		${_platform}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/cmake/templates
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/source)

	plugin_link_libraries(
		${target}
		${_backend}
		${_platform}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk)

	plugin_compile_definitions(
		${target}
		${_backend}
		${_type}
		${_company}
		${_description}
		${_version}
		${_email}
		${_website})

	plugin_bundle(
		${target}
		${_platform}
		${_company}
		${_backend})

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
