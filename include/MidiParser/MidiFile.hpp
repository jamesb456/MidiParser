#pragma once
#include <cstdint>
#include <string>
#include <filesystem>

namespace MidiParser{
    class MidiFile {
    private:
        static constexpr const uint8_t HEADER_START[] = { 0x4D, 0x54, 0x68, 0x64} ; // MThd
        static constexpr const uint8_t TRACK_START[] = { 0x4D, 0x54, 0x72, 0x6B} ; // MTrk
        static constexpr const size_t FORMAT_INDEX = 9;


        uint8_t format;

    public:
        explicit MidiFile(uint8_t format);
        uint8_t get_format() const { return this->format; };


        /// Parse the midi file at filepath.
        /// \param filepath The filepath of the MIDI file to parse
        /// \return A MidiFile object parsed from the given file
        static MidiFile parse_midi(const std::filesystem::path &filepath);
    };
}



