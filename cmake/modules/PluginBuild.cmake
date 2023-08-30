# @brief plugin_include_directories internal function
# @param target
# @param include 
function(plugin_include_directories target include)
	target_include_directories(${target} PRIVATE ${include})

	target_include_directories(libaudioplugin_validator
    	PRIVATE
        "${SMTG_AAX_SDK_PATH}/Interfaces"
        "${SMTG_AAX_SDK_PATH}/Interfaces/ACF"
        "${SMTG_AAX_SDK_PATH}/Libs/AAXLibrary/Include")
endfunction()

# @brief plugin_sources internal function
# @param target
# @param backend 
# @param platform 
# @param vst3sdk 
function(plugin_sources target backend platform vst3sdk templates)	
	if(platform STREQUAL "Windows")
		set(_main_source "${vst3sdk}/public.sdk/source/main/dllmain.cpp")
		set(_win32_resource "${templates}/win32resource.rc")
		message("-- [libaudioplugin] Adding ${_main_source}")
		message("-- [libaudioplugin] Adding ${_win32_resource}")
		target_sources(${target} PRIVATE ${_main_source})
		target_sources(${target} PRIVATE ${_win32_resource})
	elseif(platform STREQUAL "MacOS")
		set(_main_source "${vst3sdk}/public.sdk/source/main/macmain.cpp")
			# ${vst3sdk}/public.sdk/source/main/macexport.exp)
		message("-- [libaudioplugin] Adding ${_main_source}")
		target_sources(${target} PRIVATE ${_main_source})
	elseif(platform STREQUAL "Linux")
		set(_main_source "${vst3sdk}/public.sdk/source/main/linuxmain.cpp")	
		message("-- [libaudioplugin] Adding ${_main_source}")
		target_sources(${target} PRIVATE ${_main_source})
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid platform '${platform}'")
	endif()
	if (backend STREQUAL "VST2")
		set(_vst2wrapper_source "${vst3sdk}/public.sdk/source/vst/vst2wrapper/vst2wrapper.sdk.cpp")
		message("-- [libaudioplugin] Adding ${_vst2wrapper_source}")
		target_sources(${target} PRIVATE ${_vst2wrapper_source})
	endif()
endfunction()

# @brief plugin_link_libraries internal function
# @param target
# @param backend 
# @param platform 
# @param vst3sdk 
function(plugin_link_libraries target backend platform vst3sdk)
	target_link_libraries(${target} PRIVATE sdk)
	target_link_libraries(libaudioplugin_validator PRIVATE sdk)
	if(platform STREQUAL "MacOS")
		find_library(foundation_framework Foundation)
		target_link_libraries(${target} PRIVATE ${foundation_framework})
	endif()
	if(backend STREQUAL "AAX")
		target_link_libraries(${target} PRIVATE aaxwrapper)
		# target_link_libraries(libaudioplugin_validator PRIVATE aaxwrapper)
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
		target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_BACKEND_AAX)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DAUDIOPLUGIN_BACKEND_AAX)
	elseif(backend STREQUAL "AUV2")
		target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_BACKEND_AUV2)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DAUDIOPLUGIN_BACKEND_AUV2)
	elseif(backend STREQUAL "AUV3")
		target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_BACKEND_AUV3)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DAUDIOPLUGIN_BACKEND_AUV3)
	elseif(backend STREQUAL "VST2")
		target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_BACKEND_VST2)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DAUDIOPLUGIN_BACKEND_VST2)
	elseif(backend STREQUAL "VST3")
		target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_BACKEND_VST3)
		target_compile_definitions(libaudioplugin_validator PRIVATE -DAUDIOPLUGIN_BACKEND_VST3)
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid backend")
	endif()
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_NAME="${target}")
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_TYPE="${type}")
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_COMPANY="${company}")
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_DESCRIPTION="${description}")
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_VERSION="${version}")
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_EMAIL="${email}")
	target_compile_definitions(${target} PRIVATE -DAUDIOPLUGIN_PLUGIN_WEBSITE="${website}")
	target_compile_definitions(libaudioplugin_validator PRIVATE -DAUDIOPLUGIN_TEST_SUITE=${target})
endfunction()
