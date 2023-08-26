# @brief plugin_parse_platform internal function
# @param out_platform
function(plugin_parse_platform out_platform)
	if(CMAKE_SYSTEM_NAME MATCHES "Linux")
		set(${out_platform} "Linux" PARENT_SCOPE)
	elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
		set(${out_platform} "MacOS" PARENT_SCOPE)
	elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
		set(${out_platform} "Windows" PARENT_SCOPE)
	elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
		message(FATAL_ERROR "[libaudioplugin] Platform ${CMAKE_SYSTEM_NAME} not yet supported")
	elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
		message(FATAL_ERROR "[libaudioplugin] Platform ${CMAKE_SYSTEM_NAME} not yet supported")
	else()
		message(FATAL_ERROR "[libaudioplugin] Invalid platform ${CMAKE_SYSTEM_NAME}")
	endif()
endfunction()

# @brief plugin_parse_backend internal function
# @param out_backend
function(plugin_parse_backend out_backend)
	set(_available_backends "VST3")
	if(platform MATCHES "Windows" OR platform MATCHES "MacOS")
		set(_available_backends ${_available_backends} "AAX" "VST2")
	endif()
	if(platform MATCHES "MacOS")
		set(_available_backends ${_available_backends} "AUV2" "AUV3")
	endif()
	set(${out_backend} "VST2" CACHE STRING "Selected plugin backend")
	set_property(CACHE ${out_backend} PROPERTY STRINGS ${_available_backends})
endfunction()

# @brief plugin_parse_type internal function
# @param instrument
# @param fx
# @param out_type
function(plugin_parse_type instrument fx out_type)
	if(instrument)
		set(${out_type} "Instrument" PARENT_SCOPE)
	else()
		if(NOT fx)
			message("-- [libaudioplugin] Plugin type is not defined, set it with FX or INSTRUMENT")
		endif()
		set(${out_type} "Fx" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_company internal function
# @param company
# @param out_company
function(plugin_parse_company company out_company)
	if(DEFINED ${company})
		set(${out_company} ${${company}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin company is not defined, set it with COMPANY")
		set(${out_company} "MyPluginCompany" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_description internal function
# @param description
# @param out_description
function(plugin_parse_description description out_description)
	if(DEFINED ${description})
		set(${out_description} ${${description}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin description is not defined, set it with DESCRIPTION")
		set(${out_description} "My plugin description" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_description internal function
# @param description
# @param out_description
function(plugin_parse_version version out_version)
	if(DEFINED ${version})
		set(${out_version} ${${version}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin version is not defined, set it with VERSION")
		set(${out_version} "1.0.0.0" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_email internal function
# @param email
# @param out_email
function(plugin_parse_email email out_email)
	if(DEFINED ${email})
		set(${out_email} ${${email}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin email is not defined, set it with VERSION")
		set(${out_email} "info@mycompanyname.com" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_website internal function
# @param website
# @param out_website
function(plugin_parse_website website out_website)
	if(DEFINED ${website})
		set(${out_website} ${${website}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin website is not defined, set it with VERSION")
		set(${out_website} "https://www.mycompanyname.com" PARENT_SCOPE)
	endif()
endfunction()


