project(libaudioplugin_test)

# go function add_plugin_and_test

set(libaudioplugin_test_source
	"source/test_process.cpp"
# 	"source/test_process_thread.cpp"
# 	"source/test_silence_flags.cpp"
# 	"source/test_silence_processing.cpp"
# 	"source/test_flush_param.cpp"
# 	"source/test_variable_block_size.cpp"
# 	"source/test_process_format.cpp"
# 	"source/test_bypass_persistence.cpp"
# 	"source/test_automation.cpp"
# 	"source/test_editor_classes.cpp"
# 	"source/test_scan_busses.cpp"
# 	"source/test_scan_parameters.cpp"
# 	"source/test_midi_mapping.cpp"
# 	"source/test_midi_learn.cpp"
# 	"source/test_unit_info.cpp"
# 	"source/test_program_info.cpp"
# 	"source/test_terminate_initialize.cpp"
# 	"source/test_unit_structure.cpp"
# 	"source/test_.cpp"
	# createTest<ValidStateTransitionTest> (generalTests, plugProvider, kSample32);
	# createTest<ValidStateTransitionTest> (generalTests, plugProvider, kSample64);
	# //	createTest<InvalidStateTransitionTest> (generalTests, plugProvider);
	# //	createTest<RepeatIdenticalStateTransitionTest> (generalTests, plugProvider);

	# createTest<BusConsistencyTest> (generalTests, plugProvider);
	# //	createTest<BusInvalidIndexTest> (generalTests, plugProvider);
	# createTest<BusActivationTest> (generalTests, plugProvider);

	# createTest<CheckAudioBusArrangementTest> (generalTests, plugProvider);
	# createTest<SideChainArrangementTest> (generalTests, plugProvider);

	# createTest<SuspendResumeTest> (generalTests, plugProvider, kSample32);

	# createTest<NoteExpressionTest> (generalTests, plugProvider);
	# createTest<KeyswitchTest> (generalTests, plugProvider);
	# createTest<ProcessContextRequirementsTest> (generalTests, plugProvider);

)

add_executable(libaudioplugin_test "${libaudioplugin_test_source}")

set_property(TARGET libaudioplugin_test PROPERTY CXX_STANDARD 17)

target_link_libraries(libaudioplugin_test libaudioplugin_runtime)
target_link_libraries(libaudioplugin_test libaudioplugin_widgets)
target_link_libraries(libaudioplugin_test gtest_main)

add_test(NAME "libaudioplugin_test" COMMAND libaudioplugin_test)

# add_custom_command(
# 	TARGET libaudioplugin_test POST_BUILD
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:libaudioplugin_test> ${CMAKE_BINARY_DIR}/test/$<CONFIGURATION>/libaudioplugin_test)