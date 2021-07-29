#pragma once
#include <cstdint>
namespace MidiParser::Conversion{
    constexpr uint16_t from_uint8(uint8_t first, uint8_t second){
        return ( static_cast<uint16_t>(first << 8) | static_cast<uint16_t>(second));
    }



    constexpr uint32_t from_uint8(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth){
        uint32_t uint = 0;
        uint = (uint << 8) | static_cast<uint8_t>(first);
        uint = (uint << 8) | static_cast<uint8_t>(second);
        uint = (uint << 8) | static_cast<uint8_t>(third);
        uint = (uint << 8) | static_cast<uint8_t>(fourth);
        return uint;
    }
}