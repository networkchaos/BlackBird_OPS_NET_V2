#pragma once
#include <cstdint> 


//BLACKBIRD PROTOCOL by networkchaos 
//Every packet has a type field this defines all valid types of packets sent to the server and client 

namespace BRD{
//groups everything together 
  constexpr uint8_t VERSION = 1;
  //maybe upgrade to 16 bit later but for now 8 bit is fine 
  enum class PacketType : uint8_t {
    HANDSHAKE = 0x01, //establish connection 
    ECHO = 0x02, //ping packet
    DATA = 0x03, //data packet
    ACK = 0x04, //acknowledgment packet
    ERROR = 0x05, //error packet
    DISCONNECT = 0x06, //disconnect packet
    AUTH = 0x07, //Identiy for autheitication and authorization
     //add more packet types as needed

  };
 //in this fle we define  the types used in the protocol
}