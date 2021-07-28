#define BOOST_TEST_MODULE MidiParserTests
#include <filesystem>
#include <iostream>
#include <memory>
#include <MidiParser/MidiFile.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/mpl/vector.hpp>


//from SO: handy macro for multi fixture parameterized tests
#define MULTI_FIXTURE_TEST_CASE(NAME, TPARAM, ...) \
typedef boost::mpl::vector<__VA_ARGS__> NAME##_fixtures; \
BOOST_FIXTURE_TEST_CASE_TEMPLATE(NAME, TPARAM, NAME##_fixtures, TPARAM)


BOOST_AUTO_TEST_CASE(test_rejects_non_midi) {
    BOOST_CHECK_THROW(MidiParser::MidiFile::parse_midi("mid/actually_text.mid"), std::invalid_argument);
}


struct MidiFileFixture {
    virtual uint8_t get_expected_format() = 0;
    virtual uint16_t get_expected_track_num() = 0;
};

// format 1, one track
struct SingleTrackFixture: public MidiFileFixture{
    SingleTrackFixture() : file(MidiParser::MidiFile::parse_midi("mid/test_midi.mid")){

    }

    uint8_t get_expected_format() { return 1; }
    uint16_t get_expected_track_num() { return 1; }
    MidiParser::MidiFile file;
};

//format 1, two tracks

struct MultiTrackFixture: public MidiFileFixture{
    MultiTrackFixture() : file(MidiParser::MidiFile::parse_midi("mid/ashover8_pv1.mid")){

    }

    uint8_t get_expected_format() { return 1; }
    uint16_t get_expected_track_num() {return 2; }
    MidiParser::MidiFile file;
};


MULTI_FIXTURE_TEST_CASE(test_check_format, Fixture, SingleTrackFixture, MultiTrackFixture){
    auto format = Fixture::file.get_number_of_tracks();
    BOOST_CHECK_EQUAL(format, Fixture::get_expected_format());
}

MULTI_FIXTURE_TEST_CASE(test_check_track_number, Fixture, SingleTrackFixture, MultiTrackFixture){
    auto track_num = Fixture::file.get_expected_track_num();
    BOOST_CHECK_EQUAL(track_num, Fixture::get_expected_track_num());
}

