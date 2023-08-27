

# @brief plugin_configure_sdk internal function
# @param backend 
# @param platform 
# @param aaxsdk 
# @param coreaudiosdk 
# @param vst2sdk 
# @param vst3sdk 
function(plugin_configure_sdk platform available_backends aaxsdk coreaudiosdk vst2sdk vst3sdk)
	if(AAX IN_LIST available_backends)
		set(SMTG_AAX_SDK_PATH ${aaxsdk} CACHE STRING "The location where we store the AAX SDK" FORCE)
	endif()
	if(AUV2 IN_LIST available_backends OR AUV3 IN_LIST available_backends)	  
		set(SMTG_COREAUDIO_SDK_PATH ${coreaudiosdk} CACHE STRING "The location where we store the CoreAudio SDK" FORCE)
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
		message("Xcode version = ${XCODE_VERSION}")
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
		set(_default_comp_path "~/Library/Audio/Plug-Ins/Components/")
		if(NOT IS_DIRECTORY "${_default_comp_path}")
			file(MAKE_DIRECTORY "${_default_comp_path}")
			message("-- [libaudioplugin] Created ~/Library/Audio/Plug-Ins/Components/ directory")
		endif()
		smtg_add_vst3plugin(${target}_VST3 ${sources})
		smtg_target_add_auv2(${target}
			BUNDLE_NAME ${target}
			BUNDLE_IDENTIFIER com.${company}.${target}.audiounit
			INFO_PLIST_TEMPLATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../templates/au-info.plist
			VST3_PLUGIN_TARGET ${target}_VST3)
		smtg_target_configure_version_file(${target}_VST3)
		set_target_properties(${target}_VST3 PROPERTIES CXX_STANDARD 17)
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
