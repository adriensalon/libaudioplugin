

# @brief plugin_parse_backend internal function
# @param available_backends
# @param preferred_backend
# @param var_target_backend
# @param out_backend
function(plugin_parse_backend available_backends preferred_backend var_target_backend out_backend)
	if(${var_target_backend})
		set(${out_backend} ${${var_target_backend}} PARENT_SCOPE)
	else()
		set(${out_backend} ${preferred_backend} PARENT_SCOPE)
	endif()
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
# @param var_company
# @param out_company
function(plugin_parse_company var_company out_company)
	if(DEFINED ${var_company})
		set(${out_company} ${${var_company}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin company is not defined, set it with COMPANY")
		set(${out_company} "MyPluginCompany" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_description internal function
# @param var_description
# @param out_description
function(plugin_parse_description var_description out_description)
	if(DEFINED ${var_description})
		set(${out_description} ${${var_description}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin description is not defined, set it with DESCRIPTION")
		set(${out_description} "My plugin description" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_description internal function
# @param description
# @param out_description
function(plugin_parse_version var_version out_version)
	if(DEFINED ${var_version})
		set(${out_version} ${${var_version}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin version is not defined, set it with VERSION")
		set(${out_version} "1.0.0.0" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_email internal function
# @param var_email
# @param out_email
function(plugin_parse_email var_email out_email)
	if(DEFINED ${var_email})
		set(${out_email} ${${var_email}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin email is not defined, set it with VERSION")
		set(${out_email} "info@mycompanyname.com" PARENT_SCOPE)
	endif()
endfunction()

# @brief plugin_parse_website internal function
# @param website
# @param out_website
function(plugin_parse_website var_website out_website)
	if(DEFINED ${var_website})
		set(${out_website} ${${var_website}} PARENT_SCOPE)
	else()
		message("-- [libaudioplugin] Plugin website is not defined, set it with VERSION")
		set(${out_website} "https://www.mycompanyname.com" PARENT_SCOPE)
	endif()
endfunction()
