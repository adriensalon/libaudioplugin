
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

smtg_enable_vst3_sdk()

add_library(libplugin STATIC "source/libplugin.cpp")

target_include_directories(libplugin PUBLIC "include")

target_link_libraries(libplugin PUBLIC sdk)

# @param target The target that implements the libplugin interface
# @param PLUGIN_FX
# @param PLUGIN_INSTRUMENT
# @param PLUGIN_NAME <name>
# @param PLUGIN_COMPANY <company>
# @param PLUGIN_DESCRIPTION <description>
# @param PLUGIN_VERSION <version>
function(add_plugin plugin_name)
	set(options PLUGIN_FX PLUGIN_INSTRUMENT)
	set(oneValueArgs PLUGIN_COMPANY PLUGIN_DESCRIPTION PLUGIN_VERSION)
	set(multipleValuesArgs PLUGIN_SOURCES)
	cmake_parse_arguments(PARSE_ARGV 1 LIBPLUGIN "${options}" "${oneValueArgs}" "${multipleValuesArgs}")
	message("${source}")
	if(LIBPLUGIN_PLUGIN_INSTRUMENT)
		set(LIBPLUGIN_PLUGIN_TYPE "Instrument")
	else()
		if(NOT LIBPLUGIN_PLUGIN_FX)
			message("-- [libplugin] Plugin type is not defined, set it with FX or INSTRUMENT")
		endif()

		set(LIBPLUGIN_PLUGIN_TYPE "Fx")
	endif()

	if(NOT DEFINED LIBPLUGIN_PLUGIN_COMPANY)
		message("-- [libplugin] Plugin company is not defined, set it with PLUGIN_COMPANY")
		set(LIBPLUGIN_PLUGIN_COMPANY "MyPluginCompany")
	endif()

	if(NOT DEFINED LIBPLUGIN_PLUGIN_DESCRIPTION)
		message("-- [libplugin] Plugin description is not defined, set it with PLUGIN_DESCRIPTION")
		set(LIBPLUGIN_PLUGIN_DESCRIPTION "MyPluginDescription")
	endif()

	if(NOT DEFINED LIBPLUGIN_PLUGIN_VERSION)
		message("-- [libplugin] Plugin version is not defined, set it with PLUGIN_VERSION")
		set(LIBPLUGIN_PLUGIN_VERSION "1.0.0.0")
	endif()

	message("-- [libplugin] Plugin name is '${plugin_name}'")
	message("-- [libplugin] Plugin category is '${LIBPLUGIN_PLUGIN_TYPE}'")
	message("-- [libplugin] Plugin company is '${LIBPLUGIN_PLUGIN_COMPANY}'")
	message("-- [libplugin] Plugin description is '${LIBPLUGIN_PLUGIN_DESCRIPTION}'")
	message("-- [libplugin] Plugin version is '${LIBPLUGIN_PLUGIN_VERSION}'")

	project(${plugin_name}
		VERSION ${LIBPLUGIN_PLUGIN_VERSION}
		DESCRIPTION ${LIBPLUGIN_PLUGIN_DESCRIPTION})

		message("sources = ${LIBPLUGIN_PLUGIN_SOURCES}")
	smtg_add_vst3plugin(${plugin_name}
		${LIBPLUGIN_PLUGIN_SOURCES}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/source/wrapper/processor.cpp
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/source/wrapper/controller.cpp)

	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_NAME="${plugin_name}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_TYPE="${LIBPLUGIN_PLUGIN_TYPE}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_COMPANY="${LIBPLUGIN_PLUGIN_COMPANY}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_DESCRIPTION="${LIBPLUGIN_PLUGIN_DESCRIPTION}")

	# target_link_libraries(${plugin_name} PRIVATE sdk)
	target_link_libraries(${plugin_name} PRIVATE libplugin)

	smtg_target_configure_version_file(${plugin_name})

	if(SMTG_MAC)
		smtg_target_set_bundle(${plugin_name}
			BUNDLE_IDENTIFIER com.PLSOVERRIDECOMPANY.ANDNAME
			COMPANY_NAME "My Plug-in Company")

		smtg_target_set_debug_executable(${plugin_name}
			"/Applications/VST3PluginTestHost.app"
			"--pluginfolder;$(BUILT_PRODUCTS_DIR)")

	elseif(SMTG_WIN)
		target_sources(${plugin_name} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/resource/win32resource.rc)

		if(MSVC)
			set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${plugin_name})
			smtg_target_set_debug_executable(${plugin_name}
				"$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
				"--pluginfolder \"$(OutDir)/\"")
		endif()
	endif(SMTG_MAC)
endfunction()
