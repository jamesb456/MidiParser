#include <fstream>
#include <iostream>
#include <iterator>
#include <MidiParser/MidiFile.hpp>
#include <cstring>

MidiParser::MidiFile::MidiFile(uint8_t format, uint16_t track_num) : format(format), track_num(track_num) {

}


MidiParser::MidiFile MidiParser::MidiFile::parse_midi(const std::filesystem::path &filepath) {
    std::ifstream mid_file;
    mid_file.exceptions(std::ifstream::failbit);

    try{
        std::cout << "Parsing MIDI file @ " << std::filesystem::absolute(filepath) << std::endl;
        mid_file.open(filepath, std::ios::binary);
        char header_text[4];

        //first: check for MThd at the start of the MIDI file (bytes 0-3). If this
        //doesn't exist, we don't have a MIDI file!
        mid_file.read(header_text, 4);
        if(!std::equal(std::begin(header_text), std::end(header_text), std::begin(HEADER_START), std::end(HEADER_START))){

            throw std::invalid_argument("File at " + filepath.string() + " is not a MIDI file "
                                                                         "(No header chunk at start)");
        }
        // looks like a header. check bytes 4-7 for the header length
        // (should usually be 6 bytes)
        char header_length_buffer[4];
        mid_file.read(header_length_buffer, 4);

        uint32_t header_length = 0;
        for(auto& i : header_length_buffer){
            header_length = (header_length << 8) | static_cast<uint8_t>(i);
        }

        std::cout << "The header is " << header_length << " bytes long." << std::endl;

        //byte 8 to (8 + header_length_buffer - 1) contains the header information
        // 8-9: format (0-2)
        // 10-11: number of track chunks (16 bit integer)
        // 12-13: units of delta time

        //in reality, format is either 0, 1 or 2 and is msb first
        // so we don't need to use byte 8
        mid_file.ignore(1);

        uint8_t midi_format = 0;
        mid_file >> midi_format;

        std::cout << "The MIDI uses track format " << static_cast<uint32_t>(midi_format) << std::endl;

        //number of tracks (bytes 10 and 11)
        uint8_t track_num_high = 0, track_num_low = 0;
        mid_file >> track_num_high >> track_num_low;

        uint16_t track_num = ( static_cast<uint16_t>(track_num_high << 4) | static_cast<uint16_t>(track_num_low));
        std::cout << "The number of tracks is " << track_num << std::endl;


        //timing (bytes 12 and 13)


        return MidiFile(midi_format, track_num);
    } catch (const std::ifstream::failure&) {
        throw std::runtime_error(std::string("Could not parse MIDI with reason: ") + std::strerror(errno));
    }

    
}


