#pragma once 
#include "../protocol/packet.hpp"
#include "../protocol/decoder.cpp"
#include "../protocol/packet.cpp"
#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>


namespace BRD {

class Connection {
public:
    int fd;  // socket file descriptor

    explicit Connection(int sockfd) : fd(sockfd) {}

    void sendPacket(const Packet& pkt) {
        auto bytes = encode(pkt);
        // Send header first, then payload (framing)
        ssize_t sent = send(fd, bytes.data(), bytes.size(), 0);
        if (sent < 0) throw std::runtime_error("send() failed");
    }

     Packet recvPacket() {
        // Read header first — always 10 bytes
        uint8_t header[HEADER_SIZE];
        ssize_t n = recv(fd, header, HEADER_SIZE, MSG_WAITALL);
        if (n <= 0) throw std::runtime_error("Connection closed");

        // Parse length from header bytes 6–9
        uint32_t len_n;
        memcpy(&len_n, header + 6, 4);
        uint32_t payloadLen = ntohl(len_n);

        // Now read exactly payloadLen more bytes
        std::vector<uint8_t> buf(header, header + HEADER_SIZE);
        buf.resize(HEADER_SIZE + payloadLen);
        if (payloadLen > 0) {
            recv(fd, buf.data() + HEADER_SIZE, payloadLen, MSG_WAITALL);
        }

        return decode(buf);
    }

    void close() { ::close(fd); }
};



}