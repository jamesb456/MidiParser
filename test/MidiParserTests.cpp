#define BOOST_TEST_MODULE MidiParserTests
#include <filesystem>
#include <iostream>
#include <memory>
#include <MidiParser/MidiFile.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_rejects_non_midi) {
    BOOST_CHECK_THROW(MidiParser::MidiFile::parse_midi("mid/actually_text.mid"), std::invalid_argument);
}

struct MidiParserFixture{
    MidiParserFixture() : file(MidiParser::MidiFile::parse_midi("mid/test_midi.mid")){
        BOOST_TEST_MESSAGE("Setup Complete");
    }

    ~MidiParserFixture()
    {
        BOOST_TEST_MESSAGE("Teardown Complete");
    }
    MidiParser::MidiFile file;
};



BOOST_FIXTURE_TEST_CASE(test_check_format, MidiParserFixture){
    auto format = file.get_format();
    BOOST_CHECK_EQUAL(format, 1); // should be a multi track MIDI file

}

