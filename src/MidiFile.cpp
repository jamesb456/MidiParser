#include <fstream>
#include <iostream>
#include <iterator>
#include <MidiParser/MidiFile.hpp>
#include <cstring>

MidiParser::MidiFile::MidiFile(uint8_t format) : format(format) {

}


MidiParser::MidiFile MidiParser::MidiFile::parse_midi(const std::filesystem::path &filepath) {
    std::ifstream mid_file;
    mid_file.exceptions(std::ifstream::failbit);

    try{
        std::cout << "Parsing MIDI file @ " << std::filesystem::absolute(filepath) << std::endl;
        mid_file.open(filepath, std::ios::binary);
        std::vector<uint8_t> buffer; // buffer containing MIDI file
        // copy file into buffer
        std::copy(std::istreambuf_iterator<char>(mid_file),
                  std::istreambuf_iterator<char>(),
                  std::back_inserter(buffer));


        //first: check for MThd at the start of the MIDI file (bytes 1-4). If this
        //doesn't exist, we don't have a MIDI file!

        if(!std::equal(buffer.begin(), buffer.begin() + 4, std::begin(HEADER_START), std::end(HEADER_START))){
            throw std::invalid_argument("File at " + filepath.string() + " is not a MIDI file "
                                                                         "(doesn't start with MThd)");
        }
        // looks like a header. check bytes 5-8 for the header length
        // (should usually be 6 bytes)
        uint32_t header_length = 0;
        for(size_t i = 4; i < 8; i++){
            header_length = (header_length << 8) | static_cast<uint8_t>(buffer[i]);
        }

        std::cout << "The header is " << header_length << " bytes long." << std::endl;

        //byte 9 to (9 + header_length - 1) contains the header information
        // 9-10: format (0-2)
        // 11-12: number of track chunks (16 bit integer)
        // 13-14: units of delta time

        //in reality, format is either 0, 1 or 2 and is msb first
        // so we don't need to use a 16 bit number
        uint8_t midi_format = buffer[FORMAT_INDEX];
        std::cout << "The MIDI uses track format " << static_cast<uint32_t>(midi_format) << std::endl;

        return MidiFile(midi_format);
    } catch (const std::ifstream::failure&) {
        throw std::runtime_error(std::string("Could not parse MIDI with reason: ") + std::strerror(errno));
    }

    
}


