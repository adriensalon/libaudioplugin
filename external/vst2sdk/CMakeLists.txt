project(vst2sdk)

set(vst2sdk_source 
	# "public.sdk/samples/vst2.x/win/vstplug.def"
	# "public.sdk/source/vst2.x/vstplugmain.cpp"
	"public.sdk/source/vst2.x/audioeffect.cpp"
	"public.sdk/source/vst2.x/audioeffectx.cpp") 

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Android")
	set(vst2sdk_source ${vst2sdk_source} "public.sdk/source/vst2.x/vstplugmain.cpp")
endif()

add_library(vst2sdk ${vst2sdk_source})

target_include_directories(vst2sdk PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(vst2sdk PROPERTIES CXX_STANDARD 17)
