
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

smtg_enable_vst3_sdk()

# @param target The target that implements the libplugin interface
# @param PLUGIN_NAME <name>
# @param PLUGIN_COMPANY <company>
# @param PLUGIN_DESCRIPTION <description>
# @param PLUGIN_VERSION <version>
function(add_plugin target)
	set(oneValueArgs PLUGIN_NAME PLUGIN_COMPANY PLUGIN_DESCRIPTION PLUGIN_VERSION)
	cmake_parse_arguments(PARSE_ARGV 1 PARAM "" "${oneValueArgs}" "")

	if(NOT DEFINED PARAM_PLUGIN_NAME)
		message("-- [libplugin] Plugin name is not defined, set it with PLUGIN_NAME")
		set(PARAM_PLUGIN_NAME "MyPluginName")
	endif()

	if(NOT DEFINED PARAM_PLUGIN_COMPANY)
		message("-- [libplugin] Plugin company is not defined, set it with PLUGIN_COMPANY")
		set(PARAM_PLUGIN_COMPANY "MyPluginCompany")
	endif()

	if(NOT DEFINED PARAM_PLUGIN_DESCRIPTION)
		message("-- [libplugin] Plugin description is not defined, set it with PLUGIN_DESCRIPTION")
		set(PARAM_PLUGIN_DESCRIPTION "MyPluginDescription")
	endif()

	if(NOT DEFINED PARAM_PLUGIN_VERSION)
		message("-- [libplugin] Plugin version is not defined, set it with PLUGIN_VERSION")
		set(PARAM_PLUGIN_VERSION "1.0.0.0")
	endif()

	get_target_property(target_type ${target} TYPE)

	if(NOT target_type STREQUAL "STATIC_LIBRARY")
		message(FATAL_ERROR " [libplugin] Plugin target ${target} is not a static library, aborting...")
	endif()

	message("-- [libplugin] Plugin name is '${PARAM_PLUGIN_NAME}'")
	message("-- [libplugin] Plugin company is '${PARAM_PLUGIN_COMPANY}'")
	message("-- [libplugin] Plugin description is '${PARAM_PLUGIN_DESCRIPTION}'")
	message("-- [libplugin] Plugin version is '${PARAM_PLUGIN_VERSION}'")

	project(${PARAM_PLUGIN_NAME}
		VERSION ${PARAM_PLUGIN_VERSION}
		DESCRIPTION ${PARAM_PLUGIN_DESCRIPTION})

	smtg_add_vst3plugin(${PARAM_PLUGIN_NAME}
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/source/wrapper/processor.cpp
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/source/wrapper/controller.cpp
		${CMAKE_CURRENT_FUNCTION_LIST_DIR}/source/wrapper/entry.cpp)

	target_link_libraries(${PARAM_PLUGIN_NAME} PRIVATE sdk)

	smtg_target_configure_version_file(${PARAM_PLUGIN_NAME})

	if(SMTG_MAC)
		smtg_target_set_bundle(${PARAM_PLUGIN_NAME}
			BUNDLE_IDENTIFIER com.PLSOVERRIDECOMPANY.ANDNAME
			COMPANY_NAME "My Plug-in Company")

		smtg_target_set_debug_executable(${PARAM_PLUGIN_NAME}
			"/Applications/VST3PluginTestHost.app"
			"--pluginfolder;$(BUILT_PRODUCTS_DIR)")

	elseif(SMTG_WIN)
		target_sources(${PARAM_PLUGIN_NAME} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/resource/win32resource.rc)

		if(MSVC)
			set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PARAM_PLUGIN_NAME})
			smtg_target_set_debug_executable(${PARAM_PLUGIN_NAME}
				"$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
				"--pluginfolder \"$(OutDir)/\"")
		endif()
	endif(SMTG_MAC)
endfunction()
