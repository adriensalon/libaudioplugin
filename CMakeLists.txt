cmake_minimum_required(VERSION 3.14.0)

project(libplugin_all)

set(libplugin_version "v0.1.0-alpha")

if(CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Android")
	set(libplugin_platform "Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "iOS")
	set(libplugin_platform "Apple")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(libplugin_platform "Windows")
else()
	message("[libplugin] Invalid platform ${CMAKE_SYSTEM_NAME}, aborting configuration")
endif()

option(LIBPLUGIN_BUILD_DEMO "Build demo executable" ON)
option(LIBPLUGIN_BUILD_DOC "Build doxygen documentation" ON)
option(LIBPLUGIN_BUILD_TEST "Build gtest executable" ON)

option(LIBPLUGIN_BUILD_VST2 "" ON)
option(LIBPLUGIN_BUILD_VST3 "" ON)

if(libplugin_platform MATCHES "Windows" OR libplugin_platform MATCHES "Apple")
	option(LIBPLUGIN_BUILD_AAX "" ON) # + need AAX SDK!
endif()

if(libplugin_platform MATCHES "Apple")
	option(LIBPLUGIN_BUILD_AU2 "" ON)
	option(LIBPLUGIN_BUILD_AU3 "" ON)
endif()

message("-- [libplugin] Configuring for ${CMAKE_SYSTEM_NAME} platform")
message("-- [libplugin] Building demo is ${LIBPLUGIN_BUILD_DEMO}")
message("-- [libplugin] Building doc is ${LIBPLUGIN_BUILD_DOC}")
message("-- [libplugin] Building test is ${LIBPLUGIN_BUILD_TEST}")
message("-- [libplugin] Building VST2 is ${LIBPLUGIN_BUILD_VST2}")
message("-- [libplugin] Building VST3 is ${LIBPLUGIN_BUILD_VST3}")

if(libplugin_platform MATCHES "Windows" OR libplugin_platform MATCHES "Apple")
	message("-- [libplugin] Building AAX is ${LIBPLUGIN_BUILD_AAX}")
endif()

if(libplugin_platform MATCHES "Apple")
	message("-- [libplugin] Building AUv2 is ${LIBPLUGIN_BUILD_AU2}")
	message("-- [libplugin] Building AUv3 is ${LIBPLUGIN_BUILD_AU3}")
endif()

add_subdirectory(external)
add_subdirectory(libplugin)
add_subdirectory(demo)
add_subdirectory(doc)
add_subdirectory(test)
