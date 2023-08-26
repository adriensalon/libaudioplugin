cmake_minimum_required(VERSION 3.14.0)

project(libaudioplugin_all)

set(libaudioplugin_version "v0.1.0-alpha")

if(CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Android")
	set(libaudioplugin_platform "Linux")
	set(libaudioplugin_vst2_extension "so")

elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "iOS")
	set(libaudioplugin_platform "Apple")
	set(libaudioplugin_vst2_extension "vst2")

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(libaudioplugin_platform "Windows")
	set(libaudioplugin_vst2_extension "dll")

else()
	message(FATAL_ERROR "[libaudioplugin] Invalid platform ${CMAKE_SYSTEM_NAME}, aborting configuration")
endif()

set(libaudioplugin_available_backends "VST3")

if(libaudioplugin_platform MATCHES "Windows" OR libaudioplugin_platform MATCHES "Apple")
	set(libaudioplugin_available_backends ${libaudioplugin_available_backends} "AAX" "VST2")
endif()

if(libaudioplugin_platform MATCHES "Apple")
	set(libaudioplugin_available_backends ${libaudioplugin_available_backends} "AU2" "AU3")
endif()

set(LIBAUDIOPLUGIN_BUILD_BACKEND "VST2" CACHE STRING "Selected plugin backend")
set_property(CACHE LIBAUDIOPLUGIN_BUILD_BACKEND PROPERTY STRINGS ${libaudioplugin_available_backends})

if(NOT LIBAUDIOPLUGIN_BUILD_BACKEND IN_LIST libaudioplugin_available_backends)
	message(FATAL_ERROR "[libaudioplugin] Wrong value of the parameter LIBAUDIOPLUGIN_BUILD_BACKEND")
endif()

option(LIBAUDIOPLUGIN_BUILD_DOC "Build Doxygen documentation" ON)
option(LIBAUDIOPLUGIN_BUILD_EXAMPLE "Build example executable" ON)

message("-- [libaudioplugin] Configuring for ${libaudioplugin_platform} platform")
message("-- [libaudioplugin] Building for ${LIBAUDIOPLUGIN_BUILD_BACKEND} backend")
message("-- [libaudioplugin] Building doc is ${LIBAUDIOPLUGIN_BUILD_DOC}")
message("-- [libaudioplugin] Building example is ${LIBAUDIOPLUGIN_BUILD_EXAMPLE}")

add_subdirectory(external)

# @param plugin_name The target that implements the libaudioplugin interface
# @param PLUGIN_VALIDATE
# @param PLUGIN_FX
# @param PLUGIN_INSTRUMENT
# @param PLUGIN_NAME <name>
# @param PLUGIN_COMPANY <company>
# @param PLUGIN_DESCRIPTION <description>
# @param PLUGIN_VERSION <version>
# @param PLUGIN_EMAIL <email>
# @param PLUGIN_WEBSITE <website>
function(add_plugin plugin_name)
	set(options PLUGIN_VALIDATE PLUGIN_FX PLUGIN_INSTRUMENT)
	set(oneValueArgs PLUGIN_COMPANY PLUGIN_DESCRIPTION PLUGIN_VERSION PLUGIN_EMAIL PLUGIN_WEBSITE)
	set(multipleValuesArgs PLUGIN_SOURCES)
	cmake_parse_arguments(PARSE_ARGV 1 LIBAUDIOPLUGIN "${options}" "${oneValueArgs}" "${multipleValuesArgs}")

	if(LIBAUDIOPLUGIN_PLUGIN_INSTRUMENT)
		set(LIBAUDIOPLUGIN_PLUGIN_TYPE "Instrument")
	else()
		if(NOT LIBAUDIOPLUGIN_PLUGIN_FX)
			message("-- [libaudioplugin] Plugin type is not defined, set it with FX or INSTRUMENT")
		endif()

		set(LIBAUDIOPLUGIN_PLUGIN_TYPE "Fx")
	endif()

	if(NOT DEFINED LIBAUDIOPLUGIN_PLUGIN_COMPANY)
		message("-- [libaudioplugin] Plugin company is not defined, set it with PLUGIN_COMPANY")
		set(LIBAUDIOPLUGIN_PLUGIN_COMPANY "MyPluginCompany")
	endif()

	if(NOT DEFINED LIBAUDIOPLUGIN_PLUGIN_DESCRIPTION)
		message("-- [libaudioplugin] Plugin description is not defined, set it with PLUGIN_DESCRIPTION")
		set(LIBAUDIOPLUGIN_PLUGIN_DESCRIPTION "MyPluginDescription")
	endif()

	if(NOT DEFINED LIBAUDIOPLUGIN_PLUGIN_VERSION)
		message("-- [libaudioplugin] Plugin version is not defined, set it with PLUGIN_VERSION")
		set(LIBAUDIOPLUGIN_PLUGIN_VERSION "1.0.0.0")
	endif()

	if(NOT DEFINED LIBAUDIOPLUGIN_PLUGIN_EMAIL)
		message("-- [libaudioplugin] Plugin email is not defined, set it with PLUGIN_EMAIL")
		set(LIBAUDIOPLUGIN_PLUGIN_EMAIL "info@mycompanyname.com")
	endif()

	if(NOT DEFINED LIBAUDIOPLUGIN_PLUGIN_WEBSITE)
		message("-- [libaudioplugin] Plugin website is not defined, set it with PLUGIN_WEBSITE")
		set(LIBAUDIOPLUGIN_PLUGIN_WEBSITE "https://www.mycompanyname.com")
	endif()

	message("-- [libaudioplugin] Plugin name is '${plugin_name}'")
	message("-- [libaudioplugin] Plugin category is '${LIBAUDIOPLUGIN_PLUGIN_TYPE}'")
	message("-- [libaudioplugin] Plugin company is '${LIBAUDIOPLUGIN_PLUGIN_COMPANY}'")
	message("-- [libaudioplugin] Plugin description is '${LIBAUDIOPLUGIN_PLUGIN_DESCRIPTION}'")
	message("-- [libaudioplugin] Plugin version is '${LIBAUDIOPLUGIN_PLUGIN_VERSION}'")
	message("-- [libaudioplugin] Plugin email is '${LIBAUDIOPLUGIN_PLUGIN_EMAIL}'")
	message("-- [libaudioplugin] Plugin website is '${LIBAUDIOPLUGIN_PLUGIN_WEBSITE}'")

	project(${plugin_name}
		VERSION ${LIBAUDIOPLUGIN_PLUGIN_VERSION}
		DESCRIPTION ${LIBAUDIOPLUGIN_PLUGIN_DESCRIPTION})

	if(libaudioplugin_platform MATCHES "Windows")
		set(libaudioplugin_wrapper_main ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk/public.sdk/source/main/dllmain.cpp)
	
	elseif(libaudioplugin_platform MATCHES "Apple")
		set(libaudioplugin_wrapper_main 
			${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk/public.sdk/source/main/macmain.cpp
			${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk/public.sdk/source/main/macexport.exp)
	
	elseif(libaudioplugin_platform MATCHES "Linux")
		set(libaudioplugin_wrapper_main ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk/public.sdk/source/main/linuxmain.cpp)
	endif()

	set(libaudioplugin_binary_dir "${CMAKE_BINARY_DIR}/${LIBAUDIOPLUGIN_BUILD_BACKEND}/$<CONFIGURATION>")

	if(LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "AAX")
		smtg_add_aaxplugin(${plugin_name} ${LIBAUDIOPLUGIN_PLUGIN_SOURCES})
		target_sources(${plugin_name} PRIVATE ${libaudioplugin_wrapper_main})
		target_link_libraries(${plugin_name} PRIVATE aaxwrapper)
		target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_BUILD_AAX_WRAPPER)
		set(LIBAUDIOPLUGIN_BUILD_PATH ${libaudioplugin_binary_dir}/${plugin_name}.aaxplugin)
		add_custom_command(TARGET ${plugin_name} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${plugin_name}> ${LIBAUDIOPLUGIN_BUILD_PATH})
		add_custom_command(TARGET ${plugin_name} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/AAXPLUGIN)

	elseif(LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "AU2")
		target_sources(${plugin_name} PRIVATE ${libaudioplugin_wrapper_main})
		target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_BUILD_AU2_WRAPPER)

	elseif(LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "AU3")
		target_sources(${plugin_name} PRIVATE ${libaudioplugin_wrapper_main})
		target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_BUILD_AU2_WRAPPER)

	elseif(LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "VST2")
		smtg_add_vst3plugin(${plugin_name} ${LIBAUDIOPLUGIN_PLUGIN_SOURCES})
		target_sources(${plugin_name} PRIVATE
			${libaudioplugin_wrapper_main}
			${CMAKE_CURRENT_FUNCTION_LIST_DIR}/external/vst3sdk/public.sdk/source/vst/vst2wrapper/vst2wrapper.sdk.cpp)
		target_link_libraries(${plugin_name} PRIVATE vst2sdk)
		set(LIBAUDIOPLUGIN_BUILD_PATH ${libaudioplugin_binary_dir}/${plugin_name}.${libaudioplugin_vst2_extension})
		# add_custom_command(TARGET ${plugin_name} POST_BUILD
		# 	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${plugin_name}> ${LIBAUDIOPLUGIN_BUILD_PATH})
		# add_custom_command(TARGET ${plugin_name} POST_BUILD
		# 	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/VST3)
		target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_BUILD_VST2_WRAPPER)
		if(libaudioplugin_platform MATCHES "Apple")
			# set(CMAKE_FIND_FRAMEWORK ONLY)
			find_library(LIBAUDIOPLUGIN_MACOS_FOUNDATION Foundation)
			target_link_libraries(${plugin_name} PRIVATE ${LIBAUDIOPLUGIN_MACOS_FOUNDATION})
		endif()
		
	else()
		smtg_add_vst3plugin(${plugin_name} ${LIBAUDIOPLUGIN_PLUGIN_SOURCES})
		target_sources(${plugin_name} PRIVATE
			${libaudioplugin_wrapper_main})
		set(LIBAUDIOPLUGIN_BUILD_PATH ${libaudioplugin_binary_dir}/${plugin_name}.vst3)
		# # add_custom_command(TARGET ${plugin_name} PRE_BUILD
		# # 	COMMAND ${CMAKE_COMMAND} -E rm -R ${LIBAUDIOPLUGIN_BUILD_PATH})
		# add_custom_command(TARGET ${plugin_name} POST_BUILD
		# 	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${plugin_name}> ${LIBAUDIOPLUGIN_BUILD_PATH}_temp)
		# add_custom_command(TARGET ${plugin_name} POST_BUILD
		# 	COMMAND ${CMAKE_COMMAND} -E remove_directory ${LIBAUDIOPLUGIN_BUILD_PATH})
		# add_custom_command(TARGET ${plugin_name} POST_BUILD
		# 	COMMAND ${CMAKE_COMMAND} -E rename ${LIBAUDIOPLUGIN_BUILD_PATH}_temp ${LIBAUDIOPLUGIN_BUILD_PATH})
	endif()
	
	target_link_libraries(${plugin_name} PRIVATE sdk)

	target_include_directories(${plugin_name} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include)

	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_NAME="${plugin_name}")
	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_TYPE="${LIBAUDIOPLUGIN_PLUGIN_TYPE}")
	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_COMPANY="${LIBAUDIOPLUGIN_PLUGIN_COMPANY}")
	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_DESCRIPTION="${LIBAUDIOPLUGIN_PLUGIN_DESCRIPTION}")
	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_VERSION="${LIBAUDIOPLUGIN_PLUGIN_VERSION}")
	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_EMAIL="${LIBAUDIOPLUGIN_PLUGIN_EMAIL}")
	target_compile_definitions(${plugin_name} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_WEBSITE="${LIBAUDIOPLUGIN_PLUGIN_WEBSITE}")

	smtg_target_configure_version_file(${plugin_name})

	if(SMTG_MAC)
		smtg_target_set_bundle(${plugin_name}
			BUNDLE_IDENTIFIER com.${LIBAUDIOPLUGIN_PLUGIN_COMPANY}.${plugin_name}
			COMPANY_NAME "${LIBAUDIOPLUGIN_PLUGIN_COMPANY}")

	# smtg_target_set_debug_executable(${plugin_name}
	# "/Applications/VST3PluginTestHost.app"
	# "--pluginfolder;$(BUILT_PRODUCTS_DIR)")
	elseif(SMTG_WIN)
		target_sources(${plugin_name} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/resource/win32resource.rc)

		if(MSVC)
			set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${plugin_name})

			# smtg_target_set_debug_executable(${plugin_name}
			# "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
			# "--pluginfolder \"$(OutDir)/\"")
		endif()
	endif(SMTG_MAC)

	# Validate step
	if(LIBAUDIOPLUGIN_PLUGIN_VALIDATE)
		
		# VST2 & VST2 validator that came with the VST3 SDK
		if(LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "VST2" OR LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "VST3")
			smtg_target_run_vst_validator(${plugin_name})

		# AU validator that comes with MacOS
		elseif(LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "AU2" OR LIBAUDIOPLUGIN_BUILD_BACKEND STREQUAL "AU3")
			add_custom_command(TARGET ${plugin_name} POST_BUILD
			COMMAND auval -v ${plugin_name}) # !!!!!!!!!!!!!!

		endif()

		# No validator for AAX go ask Avid

	endif()
endfunction()

if(LIBAUDIOPLUGIN_BUILD_DOC)
	add_subdirectory(doc)
endif()

if(LIBAUDIOPLUGIN_BUILD_EXAMPLE)
	add_subdirectory(example)
endif()

