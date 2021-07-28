set(PUBLIC_HEADERS "${MidiParser_SOURCE_DIR}/include/MidiParser")
set(HEADER_LIST "${PUBLIC_HEADERS}/MidiFile.hpp")
set(SOURCE_LIST MidiFile.cpp)


add_library(MidiParser ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(MidiParser PUBLIC "${MidiParser_SOURCE_DIR}/include")

target_compile_features(MidiParser PUBLIC cxx_std_17)

