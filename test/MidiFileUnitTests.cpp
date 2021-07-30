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




struct MidiFileFixture {
    virtual uint8_t get_expected_format() const = 0;
    virtual uint16_t get_expected_track_num() const = 0;
    virtual uint32_t get_expected_tpq() const = 0;

};

// format 1, one track
struct SingleTrackFixture: public MidiFileFixture{
    SingleTrackFixture() : file(MidiParser::MidiFile::parse_midi("mid/test_midi.mid")){

    }

    uint8_t get_expected_format() const override { return 1; }
    uint16_t get_expected_track_num() const override { return 1; }
    uint32_t get_expected_tpq() const override { return 480; }
    MidiParser::MidiFile file;
};


struct SingleTrackFormatZeroFixture: public MidiFileFixture{
    SingleTrackFormatZeroFixture() : file(MidiParser::MidiFile::parse_midi("mid/test_midi_format_0.mid")){

    }
    uint8_t get_expected_format() const override { return 0; }
    uint16_t get_expected_track_num() const override { return 1; }
    uint32_t get_expected_tpq() const override { return 480; }
    MidiParser::MidiFile file;
};

//format 1, two tracks

struct MultiTrackFixture: public MidiFileFixture{
    MultiTrackFixture() : file(MidiParser::MidiFile::parse_midi("mid/ashover8.mid")){

    }

    uint8_t get_expected_format() const override { return 1; }
    uint16_t get_expected_track_num() const override {return 2; }
    uint32_t get_expected_tpq() const override { return 1024; }
    MidiParser::MidiFile file;
};

//format 2 tests coming later

BOOST_AUTO_TEST_CASE(test_rejects_non_midi) {
    BOOST_CHECK_THROW(MidiParser::MidiFile::parse_midi("mid/actually_text.mid"), std::invalid_argument);
}


MULTI_FIXTURE_TEST_CASE(test_check_format, Fixture, SingleTrackFixture, SingleTrackFormatZeroFixture ,MultiTrackFixture){
    auto format = Fixture::file.get_format();
    BOOST_CHECK_EQUAL(format, Fixture::get_expected_format());
}

MULTI_FIXTURE_TEST_CASE(test_check_track_number, Fixture, SingleTrackFixture, SingleTrackFormatZeroFixture , MultiTrackFixture){
    auto track_num = Fixture::file.get_number_of_tracks();
    BOOST_CHECK_EQUAL(track_num, Fixture::get_expected_track_num());
}

// we are not looking at smpte based files just yet
// need to create new fixtures and get an example file
MULTI_FIXTURE_TEST_CASE(test_check_ticks_per_quarter, Fixture, SingleTrackFixture, SingleTrackFormatZeroFixture ,MultiTrackFixture){
    auto ticks_per_quarter = Fixture::file.get_ticks_per_quarter();
    BOOST_CHECK_EQUAL(ticks_per_quarter, Fixture::get_expected_tpq());
}

