

function(plugin_fetch_aaxsdk aaxsdk)
	if(NOT EXISTS "${aaxsdk}/Interfaces/AAX.h")
		# if dir exists FATAL_ERROR
		file(DOWNLOAD
		https://learn-cdn.avid.com/cpp_toolkits/aax-sdk-2-5-1.zip
			${CMAKE_BINARY_DIR}/fetched/zip/aaxsdk.zip)			
			file(ARCHIVE_EXTRACT 
			INPUT ${CMAKE_BINARY_DIR}/fetched/zip/aaxsdk.zip 
			DESTINATION ${CMAKE_BINARY_DIR}/fetched/extracted/aaxsdk)
		file(RENAME 
			${CMAKE_BINARY_DIR}/fetched/extracted/aaxsdk/aax-sdk-2-5-1
			${aaxsdk})
		file(REMOVE ${CMAKE_BINARY_DIR}/fetched/zip/aaxsdk.zip)
		file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/fetched/extracted/aaxsdk)
	endif()
endfunction()


function(plugin_fetch_coreaudiosdk coreaudiosdk)
	# if(_platform STREQUAL "MacOS" AND NOT EXISTS "${coreaudiosdk}/AudioUnits/AUPublic/AUBase/AUBase.cpp")
	if(NOT EXISTS "${coreaudiosdk}/AudioUnits/AUPublic/AUBase/AUBase.cpp")
		# if dir exists FATAL_ERROR
		file(DOWNLOAD
			https://developer.apple.com/library/archive/samplecode/CoreAudioUtilityClasses/CoreAudioUtilityClasses.zip
			${CMAKE_BINARY_DIR}/fetched/zip/coreaudiosdk.zip)			
		file(ARCHIVE_EXTRACT 
			INPUT ${CMAKE_BINARY_DIR}/fetched/zip/coreaudiosdk.zip 
			DESTINATION ${CMAKE_BINARY_DIR}/fetched/extracted/coreaudiosdk)
		file(RENAME 
			${CMAKE_BINARY_DIR}/fetched/extracted/coreaudiosdk/CoreAudioUtilityClasses/CoreAudio
			${coreaudiosdk})
		file(REMOVE ${CMAKE_BINARY_DIR}/fetched/zip/coreaudiosdk.zip)
		file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/fetched/extracted/coreaudiosdk)
	endif()
endfunction()

