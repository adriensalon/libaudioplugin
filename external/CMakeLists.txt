set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "We do not need examples." FORCE)
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "We do not need examples." FORCE)
set(SMTG_ENABLE_VSTGUI_SUPPORT OFF CACHE BOOL "We do not need VSTGUI." FORCE)

# SMTG_BUILD_UNIVERSAL_BINARY mac only
# SMTG_CREATE_BUNDLE_FOR_WINDOWS
set(SMTG_CREATE_PLUGIN_LINK OFF CACHE BOOL "We do not need to create simlinks." FORCE)
set(SMTG_CREATE_VST2_AGAIN_SAMPLE_VERSION OFF CACHE BOOL "We do not need examples." FORCE)
set(SMTG_CXX_STANDARD "17" CACHE STRING "We use C++17." FORCE)
set(SMTG_ENABLE_ADDRESS_SANITIZER OFF CACHE BOOL "We trust Steinberg I guess." FORCE)

# SMTG_ENABLE_TARGET_VARS_LOG bizarre
set(SMTG_ENABLE_USE_OF_JACK OFF CACHE BOOL "We do not need Jack." FORCE)
set(SMTG_MDA_VST3_VST2_COMPATIBLE ON CACHE BOOL "We do not need this." FORCE)

# SMTG_IOS_DEVELOPMENT_TEAM: Needed for building the InterAppAudio and AUv3 examples for iOS (Mac only)
# SMTG_MYPLUGINS_SRC_PATH: Here you can add your VST 3 plug-ins folder
# SMTG_PLUGIN_TARGET_PATH: Here you can redefine the VST 3 plug-ins folder
# SMTG_PLUGIN_TARGET_USER_PROGRAM_FILES_COMMON: use FOLDERID_UserProgramFilesCommon as VST 3 target path (Windows only) (default ON)
# SMTG_RENAME_ASSERT: Rename ASSERT to SMTG_ASSERT to avoid conflicts with 3rd party libraries (default ON)
# SMTG_RUN_VST_VALIDATOR: Run the VST validator on VST 3 plug-ins each time they are built (default ON)

# Use static CRuntime on Windows (option /MT) (default OFF: /MD is used) (Windows only)
set(SMTG_USE_STATIC_CRT OFF CACHE BOOL "Test." FORCE)

add_subdirectory(vst3sdk)
target_include_directories(sdk PUBLIC vst3sdk)

if(LIBPLUGIN_BUILD_VST2)
	add_subdirectory(vst2sdk)
	target_include_directories(sdk PUBLIC vst2sdk)
	# target_link_libraries(sdk PUBLIC $<LINK_LIBRARY:WHOLE_ARCHIVE,vst2sdk>)
endif()

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

smtg_enable_vst3_sdk()