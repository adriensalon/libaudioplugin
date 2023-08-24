
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

smtg_enable_vst3_sdk()

# @param plugin_name The target that implements the libplugin interface
# @param PLUGIN_FX
# @param PLUGIN_INSTRUMENT
# @param PLUGIN_NAME <name>
# @param PLUGIN_COMPANY <company>
# @param PLUGIN_DESCRIPTION <description>
# @param PLUGIN_VERSION <version>
# @param PLUGIN_EMAIL <email>
# @param PLUGIN_WEBSITE <website>
function(add_plugin plugin_name)
	set(options PLUGIN_FX PLUGIN_INSTRUMENT)
	set(oneValueArgs PLUGIN_COMPANY PLUGIN_DESCRIPTION PLUGIN_VERSION PLUGIN_EMAIL PLUGIN_WEBSITE)
	set(multipleValuesArgs PLUGIN_SOURCES)
	cmake_parse_arguments(PARSE_ARGV 1 LIBPLUGIN "${options}" "${oneValueArgs}" "${multipleValuesArgs}")
	
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

	if(NOT DEFINED LIBPLUGIN_PLUGIN_EMAIL)
		message("-- [libplugin] Plugin email is not defined, set it with PLUGIN_EMAIL")
		set(LIBPLUGIN_PLUGIN_EMAIL "info@mycompanyname.com")
	endif()

	if(NOT DEFINED LIBPLUGIN_PLUGIN_WEBSITE)
		message("-- [libplugin] Plugin website is not defined, set it with PLUGIN_WEBSITE")
		set(LIBPLUGIN_PLUGIN_WEBSITE "https://www.mycompanyname.com")
	endif()

	message("-- [libplugin] Plugin name is '${plugin_name}'")
	message("-- [libplugin] Plugin category is '${LIBPLUGIN_PLUGIN_TYPE}'")
	message("-- [libplugin] Plugin company is '${LIBPLUGIN_PLUGIN_COMPANY}'")
	message("-- [libplugin] Plugin description is '${LIBPLUGIN_PLUGIN_DESCRIPTION}'")
	message("-- [libplugin] Plugin version is '${LIBPLUGIN_PLUGIN_VERSION}'")
	message("-- [libplugin] Plugin email is '${LIBPLUGIN_PLUGIN_EMAIL}'")
	message("-- [libplugin] Plugin website is '${LIBPLUGIN_PLUGIN_WEBSITE}'")

	project(${plugin_name}
		VERSION ${LIBPLUGIN_PLUGIN_VERSION}
		DESCRIPTION ${LIBPLUGIN_PLUGIN_DESCRIPTION})

	smtg_add_vst3plugin(${plugin_name} ${LIBPLUGIN_PLUGIN_SOURCES})

	target_link_libraries(${plugin_name} PRIVATE sdk)

	target_include_directories(${plugin_name} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include)

	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_NAME="${plugin_name}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_TYPE="${LIBPLUGIN_PLUGIN_TYPE}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_COMPANY="${LIBPLUGIN_PLUGIN_COMPANY}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_DESCRIPTION="${LIBPLUGIN_PLUGIN_DESCRIPTION}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_VERSION="${LIBPLUGIN_PLUGIN_VERSION}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_EMAIL="${LIBPLUGIN_PLUGIN_EMAIL}")
	target_compile_definitions(${plugin_name} PUBLIC -DLIBPLUGIN_PLUGIN_WEBSITE="${LIBPLUGIN_PLUGIN_WEBSITE}")

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
