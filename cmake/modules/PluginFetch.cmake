# @brief plugin_detect_backend internal function
# @param out_platform
# @param out_available_backends
function(plugin_detect_backend out_platform out_available_backends)
	if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(${out_platform} "Linux" PARENT_SCOPE)
		set(_detected_backends VST3)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
		set(${out_platform} "MacOS" PARENT_SCOPE)
		set(_detected_backends AAX AUV2 AUV3 VST2 VST3)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set(${out_platform} "Windows" PARENT_SCOPE)
		set(_detected_backends AAX VST2 VST3)
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
		message(FATAL_ERROR "[libaudioplugin] Platform ${CMAKE_SYSTEM_NAME} not yet supported")
	elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
		message(FATAL_ERROR "[libaudioplugin] Platform ${CMAKE_SYSTEM_NAME} not yet supported")
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid platform ${CMAKE_SYSTEM_NAME}")
	endif()
	set(${out_available_backends} ${_detected_backends} PARENT_SCOPE)
endfunction()

# @brief plugin_fetch_sdk internal function
# @param available_backends
# @param aaxsdk
# @param coreaudiosdk
function(plugin_fetch_sdk available_backends aaxsdk coreaudiosdk)
	if(AAX IN_LIST available_backends)
		if(NOT EXISTS "${aaxsdk}/Interfaces/AAX.h")
			if(IS_DIRECTORY "${aaxsdk}")
				message("-- [libaudioplugin] Invalid AAX SDK at ${aaxsdk}")
				file(REMOVE_RECURSE ${aaxsdk})
			endif()
			set(_sdk_url https://learn-cdn.avid.com/cpp_toolkits/aax-sdk-2-5-1.zip)
			message("-- [libaudioplugin] Downloading AAX SDK from ${_sdk_url}")
			file(DOWNLOAD ${_sdk_url}
				${CMAKE_BINARY_DIR}/fetch_cache/zip/aaxsdk.zip)			
				file(ARCHIVE_EXTRACT 
				INPUT ${CMAKE_BINARY_DIR}/fetch_cache/zip/aaxsdk.zip 
				DESTINATION ${CMAKE_BINARY_DIR}/fetch_cache/extracted/aaxsdk)
			file(RENAME 
				${CMAKE_BINARY_DIR}/fetch_cache/extracted/aaxsdk/aax-sdk-2-5-1
				${aaxsdk})
			file(REMOVE ${CMAKE_BINARY_DIR}/fetch_cache/zip/aaxsdk.zip)
			file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/fetch_cache/extracted/aaxsdk)
		endif()
	endif()
	if(AUV2 IN_LIST available_backends OR AUV3 IN_LIST available_backends)
		if(NOT EXISTS "${coreaudiosdk}/AudioUnits/AUPublic/AUBase/AUBase.cpp")
			if(IS_DIRECTORY "${coreaudiosdk}")
				message("-- [libaudioplugin] Invalid CoreAudio SDK at ${coreaudiosdk}")
				file(REMOVE_RECURSE ${coreaudiosdk})
			endif()
			set(_sdk_url https://developer.apple.com/library/archive/samplecode/CoreAudioUtilityClasses/CoreAudioUtilityClasses.zip)
			message("-- [libaudioplugin] Downloading CoreAudio SDK from ${_sdk_url}")
			file(DOWNLOAD ${_sdk_url}			
				${CMAKE_BINARY_DIR}/fetch_cache/zip/coreaudiosdk.zip)			
			file(ARCHIVE_EXTRACT 
				INPUT ${CMAKE_BINARY_DIR}/fetch_cache/zip/coreaudiosdk.zip 
				DESTINATION ${CMAKE_BINARY_DIR}/fetch_cache/extracted/coreaudiosdk)
			file(RENAME 
				${CMAKE_BINARY_DIR}/fetch_cache/extracted/coreaudiosdk/CoreAudioUtilityClasses/CoreAudio
				${coreaudiosdk})
			file(REMOVE ${CMAKE_BINARY_DIR}/fetch_cache/zip/coreaudiosdk.zip)
			file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/fetch_cache/extracted/coreaudiosdk)
		endif()
	endif()
endfunction()

