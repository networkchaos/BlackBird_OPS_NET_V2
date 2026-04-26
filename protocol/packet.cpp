#include "packet.hpp"


namespace BRD{
    Packet::Packet(PacketType t , uint32_t s , const std::string& data)
     : version(VERSION), type(t), seq(s),//set length to the size of the data string 
       length(data.size()), //set length to the size of the data string 
       payload(data.begin(), data.end()) //copy string data into payload vector
       {}
}