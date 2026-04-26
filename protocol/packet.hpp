#pragma once 
#include "types.hpp"
#include <vector> // dynamic byte buffer 
#include <string> //easy input 
#include <cstring>  //low level memory ops 

//in this file we define the struct for the packet 

namespace BRD{
    //wire formart (what actually goes on the network )
    // [version : 1 byte]  
    //[type : 1byte]
    //[seq : 4 bytes ] big endian
    //[length : 4 bytes ] big endian
    //[payload : N bytes ]
    //Total header = 10 bythes 

    //equivalent idea from RFC 793 and RFC 768

    constexpr size_t HEADER_SIZE = 10 ;
    constexpr size_t MAX_PAYLOAD = 65535; // safe limit , prevents memory attacks and ensures we can handle the packet in memory(2^16 -1)

    struct Packet{
        uint8_t version;
        PacketType type;
        uint32_t seq; //squence number for ordering and reliability
        uint32_t length; //count
        std::vector<uint8_t> payload; //actual payload store on the heap

        //convinience constructor for creating packets
        Packet(PacketType t, uint32_t seq , const std::string& data);
        Packet() = default;


    };


}

