project(MidiParserTests)
set (Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)


add_executable(MidiParserTests MidiParserTests.cpp)

target_link_libraries(MidiParserTests Boost::unit_test_framework)
target_link_libraries(MidiParserTests MidiParser)
target_compile_features(MidiParserTests PUBLIC cxx_std_17)

set_property(TARGET MidiParserTests PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")