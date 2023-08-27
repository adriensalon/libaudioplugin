# @brief plugin_configure_platform internal function
# @param aaxsdk
# @param out_platform
# @param out_available_backends
function(plugin_configure_platform aaxsdk out_platform out_available_backends)
	if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(${out_platform} "Linux" PARENT_SCOPE)
		set(_detected_backends VST3)
		set(_aax_available OFF)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
		set(${out_platform} "MacOS" PARENT_SCOPE)
		set(_detected_backends AUV2 AUV3 VST2 VST3)
		set(_aax_available ON)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set(${out_platform} "Windows" PARENT_SCOPE)
		set(_detected_backends VST2 VST3)
		set(_aax_available ON)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
		message(FATAL_ERROR "[libaudioplugin] Platform ${CMAKE_SYSTEM_NAME} not yet supported")
	elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
		message(FATAL_ERROR "[libaudioplugin] Platform ${CMAKE_SYSTEM_NAME} not yet supported")
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid platform ${CMAKE_SYSTEM_NAME}")
	endif()	
	if(_aax_available)
		if(EXISTS "${aaxsdk}/Interfaces/AAX.h")
			set(_detected_backends AAX ${_detected_backends})
		else()
			message("[libaudioplugin] AAX SDK not found")
		endif()
	endif()
	set(${out_available_backends} ${_detected_backends} PARENT_SCOPE)
endfunction()

# @brief plugin_configure_sdk internal function
# @param backend 
# @param platform 
# @param aaxsdk 
# @param ausdk 
# @param vst2sdk 
# @param vst3sdk 
function(plugin_configure_sdk platform available_backends aaxsdk ausdk vst2sdk vst3sdk)
	if(AAX IN_LIST available_backends)
		set(SMTG_AAX_SDK_PATH ${aaxsdk} CACHE STRING "The location where we store the AAX SDK" FORCE)
	endif()
	set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "We do not need examples" FORCE)
	set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "We do not need examples" FORCE)
	set(SMTG_ENABLE_VSTGUI_SUPPORT OFF CACHE BOOL "We do not need VSTGUI (for now)" FORCE)
	set(SMTG_BUILD_UNIVERSAL_BINARY ON CACHE BOOL "We build universal binaries on MacOS" FORCE)
	set(SMTG_CREATE_BUNDLE_FOR_WINDOWS ON CACHE BOOL "Throws CMake warnings otherwise" FORCE)
	set(SMTG_CREATE_PLUGIN_LINK OFF CACHE BOOL "We do not need to create simlinks" FORCE)
	set(SMTG_CREATE_VST2_AGAIN_SAMPLE_VERSION OFF CACHE BOOL "We do not need examples" FORCE)
	# SMTG_CUSTOM_BINARY_LOCATION
	set(SMTG_CXX_STANDARD "17" CACHE STRING "We use C++17" FORCE)
	set(SMTG_ENABLE_ADDRESS_SANITIZER ON CACHE BOOL "We trust Steinberg I guess" FORCE)
	# SMTG_ENABLE_TARGET_VARS_LOG bizarre
	set(SMTG_ENABLE_USE_OF_JACK OFF CACHE BOOL "We do not need Jack (for standalone)" FORCE)
	set(SMTG_MDA_VST3_VST2_COMPATIBLE OFF CACHE BOOL "We do not need this" FORCE)
	# SMTG_IOS_DEVELOPMENT_TEAM: Needed for building the InterAppAudio and AUv3 examples for iOS (Mac only)
	# SMTG_MYPLUGINS_SRC_PATH: Here you can add your VST 3 plug-ins folder
	# SMTG_PLUGIN_TARGET_PATH: Here you can redefine the VST 3 plug-ins folder
	# SMTG_PLUGIN_TARGET_USER_PROGRAM_FILES_COMMON: use FOLDERID_UserProgramFilesCommon as VST 3 target path (Windows only) (default ON)
	# SMTG_RENAME_ASSERT: Rename ASSERT to SMTG_ASSERT to avoid conflicts with 3rd party libraries (default ON)
	set(SMTG_RUN_VST_VALIDATOR OFF CACHE BOOL "We run this manually" FORCE)
	set(SMTG_USE_STATIC_CRT OFF CACHE BOOL "IDK bro" FORCE)
	add_subdirectory(${vst3sdk})	
	target_include_directories(sdk PUBLIC ${vst3sdk})
	if(AAX IN_LIST available_backends)	
		list(APPEND CMAKE_MODULE_PATH "${vst3sdk}/cmake/modules")
		include(SMTG_AddAAXLibrary)
	endif()
	if(AUV2 IN_LIST available_backends)	
		list(APPEND CMAKE_MODULE_PATH "${vst3sdk}/cmake/modules")
		include(SMTG_AddVST3AuV2)	
	endif()
	if(VST2 IN_LIST available_backends)	
		add_subdirectory(${vst2sdk})
		target_include_directories(sdk PUBLIC ${vst2sdk})	
		if(platform MATCHES "Windows")
			target_compile_definitions(vst2sdk PUBLIC -D_CRT_SECURE_NO_WARNINGS)
		endif()
	endif()
	set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")
	smtg_enable_vst3_sdk()
endfunction()

# @brief plugin_configure_target internal function
# @param target
# @param company 
# @param backend 
# @param sources 
# @param vst3sdk 
function(plugin_configure_target target company backend sources vst3sdk)
	if(backend STREQUAL "AAX")
		smtg_add_aaxplugin(${target} ${sources})
	elseif(backend STREQUAL "AUV2")
		smtg_target_add_auv2(${target}
			BUNDLE_NAME ${target}
			BUNDLE_IDENTIFIER com.${company}.${target}.audiounit
			INFO_PLIST_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/resource/au-info.plist #configure from here
			VST3_PLUGIN_TARGET ${target})
	elseif(backend STREQUAL "AUV3")
		# TODO
	elseif(backend STREQUAL "VST2")
		smtg_add_vst3plugin(${target} ${sources})
		target_sources(${target} PRIVATE ${vst3sdk}/public.sdk/source/vst/vst2wrapper/vst2wrapper.sdk.cpp)
	else()
		smtg_add_vst3plugin(${target} ${sources})
	endif()
	smtg_target_configure_version_file(${target})
	set_target_properties(${target} PROPERTIES CXX_STANDARD 17)
endfunction()
