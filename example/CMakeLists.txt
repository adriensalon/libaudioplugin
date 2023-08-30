project(libaudioplugin_example)

add_plugin(ExamplePlugin
	BACKEND VST2 # We comment this for CI so we can use the preferred backend
	# VALIDATE
	SOURCES 
		source/myplugincontroller.h
		source/myplugincontroller.cpp
		source/mypluginentry.cpp
		source/mypluginprocessor.h
		source/mypluginprocessor.cpp
	FX
	COMPANY "adriensalon"
	DESCRIPTION "An example plugin"
	VERSION "1.0.0.0"
	EMAIL "mail@me.com"
	WEBSITE "mywebsite.com")