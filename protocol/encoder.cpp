#include "packet.hpp"
#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
#endif //for htonl and ntohl


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
        uint32_t seq_n = htonl(pkt.seq);
        uint8_t* seq_bytes = reinterpret_cast<uint8_t*>(&seq_n);
        buf.insert(buf.end(),seq_bytes, seq_bytes +4);

        //length - 4 bytes , big endian
        uint32_t len_n = htonl(pkt.length);
         uint8_t* len_bytes = reinterpret_cast<uint8_t*>(&len_n);
        buf.insert(buf.end(), len_bytes, len_bytes + 4);

        // payload
        buf.insert(buf.end(), pkt.payload.begin(), pkt.payload.end());

        return buf;




    }
}