project(libplugin_doc)

find_package(Doxygen QUIET)

if(DOXYGEN_FOUND)
	mark_as_advanced(DOXYGEN_EXECUTABLE)
endif()

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/doc/doxygen/")

add_custom_target(libaudioplugin_doc ALL
	COMMAND ${DOXYGEN_EXECUTABLE} "doc/Doxyfile"
	WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/.."
	VERBATIM
	USES_TERMINAL)
