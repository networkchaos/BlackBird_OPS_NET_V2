#include "packet.hpp"
#include <winsock2.h> //for htonl and ntohl


namespace BRD{
    //Encode a packet into a byte buffer ready to send 
    std::vector<uint8_t> encode( const Packet& pkt){
        std::vector<uint8_t> buf;
        buf.reserve(HEADER_SIZE + pkt.payload.size());


        //version 
        buf.push_back(pkt.version);
        //types
        buf.push_back(static_cast<uint8_t>(pkt.type));
        //sequence number (convert to network byte order)

    }
}