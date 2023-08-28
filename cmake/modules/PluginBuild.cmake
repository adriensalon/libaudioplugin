# @brief plugin_include_directories internal function
# @param target
# @param include 
function(plugin_include_directories target include)
	target_include_directories(${target} 
		PRIVATE ${include})
endfunction()

# @brief plugin_sources internal function
# @param target
# @param backend 
# @param platform 
# @param vst3sdk 
function(plugin_sources target backend platform vst3sdk)	
	if(platform STREQUAL "Windows")
		set(_sources ${vst3sdk}/public.sdk/source/main/dllmain.cpp)
		# target_sources(${target} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/resource/win32resource.rc) PAS ICI EN VRAI
	elseif(platform STREQUAL "MacOS")
		set(_sources 
			${vst3sdk}/public.sdk/source/main/macmain.cpp)
			# ${vst3sdk}/public.sdk/source/main/macexport.exp)
	elseif(platform STREQUAL "Linux")
		set(_sources ${vst3sdk}/public.sdk/source/main/linuxmain.cpp)	
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid platform '${platform}'")
	endif()
	if (backend STREQUAL "VST2")
		list(APPEND _sources ${vst3sdk}/public.sdk/source/vst/vst2wrapper/vst2wrapper.sdk.cpp)
	endif()
	target_sources(${target} PRIVATE ${_sources})
endfunction()

# @brief plugin_link_libraries internal function
# @param target
# @param backend 
# @param platform 
# @param vst3sdk 
function(plugin_link_libraries target backend platform vst3sdk)
	target_link_libraries(${target} PRIVATE base pluginterfaces sdk)
	if(platform STREQUAL "MacOS")
		find_library(foundation_framework Foundation)
		target_link_libraries(${target} PRIVATE ${foundation_framework})
	endif()
	if(backend STREQUAL "AAX")
		target_link_libraries(${target} PRIVATE aaxwrapper)
	elseif(backend STREQUAL "AUV2")
		target_link_libraries(${target} PRIVATE auwrapper)
	elseif(backend STREQUAL "VST2")
		target_link_libraries(${target} PRIVATE vst2sdk)
	endif()
endfunction()

# @brief plugin_compile_definitions internal function
# @param target
# @param backend 
# @param type 
# @param company 
# @param description 
# @param version 
# @param email 
# @param website 
function(plugin_compile_definitions target backend type company description version email website)
	if(backend STREQUAL "AAX")
		target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_BUILD_AAX_WRAPPER)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DLIBAUDIOPLUGIN_BUILD_AAX_WRAPPER)
	elseif(backend STREQUAL "AUV2")
		target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_BUILD_AUV2_WRAPPER)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DLIBAUDIOPLUGIN_BUILD_AUV2_WRAPPER)
	elseif(backend STREQUAL "AUV3")
		target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_BUILD_AUV3_WRAPPER)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DLIBAUDIOPLUGIN_BUILD_AUV3_WRAPPER)
	elseif(backend STREQUAL "VST2")
		target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_BUILD_VST2_WRAPPER)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DLIBAUDIOPLUGIN_BUILD_VST2_WRAPPER)
	elseif(backend STREQUAL "VST3")
		target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_BUILD_VST3_WRAPPER)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DLIBAUDIOPLUGIN_BUILD_VST3_WRAPPER)
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid backend")
	endif()
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_NAME="${target}")
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_TYPE="${type}")
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_COMPANY="${company}")
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_DESCRIPTION="${description}")
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_VERSION="${version}")
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_EMAIL="${email}")
	target_compile_definitions(${target} PRIVATE -DLIBAUDIOPLUGIN_PLUGIN_WEBSITE="${website}")
endfunction()
