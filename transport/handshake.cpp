// create a handshake for the transport layer 
#pragma once 
#include <sodium.h>
#include <stdexcept>
#include <cstring>
#include "connection.cpp"

namespace BRD {
    struct SessionKeys{
        uint8_t tx[crypto_secretbox_KEYBYTES]; //key to encrypt outgoing
        uint8_t rx[crypto_secretbox_KEYBYTES]; //key to decrypt incoming

    };


    SessionKeys serverHandshake(Connection& conn){
        //Genreating key pairs 
        uint8_t server_pk[crypto_kx_PUBLICKEYBYTES];
        uint8_t server_sk[crypto_kx_SECRETKEYBYTES];
        crypto_kx_keypair(server_pk, server_sk);

        //receive clients public key (raw 32 bytes )
        uint8_t client_pk[crypto_kx_PUBLICKEYBYTES];
        recv(conn.fd, client_pk, sizeof(client_pk), MSG_WAITALL);

        //send our public key 
        send(conn.fd, server_pk, sizeof(server_pk),0);

        //Derive shared session keys 
        SessionKeys keys;
        if (crypto_kx_server_session_keys(
            keys.rx, keys.tx,
            server_pk, server_sk, client_pk) != 0){
                throw std::runtime_error("Handshake failed - suspect client");

            }
            //erase secrets key after use in ram
            sodium_memzero(server_sk, sizeof(server_sk));
            return keys;

    }

//client side: send our public key , receive servers derive shared keys
SessionKeys clientHandshake(Connection& conn){
    uint8_t client_pk[crypto_kx_PUBLICKEYBYTES];
    uint8_t client_sk[crypto_kx_SECRETKEYBYTES];
    crypto_kx_keypair(client_pk, client_sk);

    // Send our public key first
    send(conn.fd, client_pk, sizeof(client_pk), 0);

    // Receive server's public key
    uint8_t server_pk[crypto_kx_PUBLICKEYBYTES];
    recv(conn.fd, server_pk, sizeof(server_pk), MSG_WAITALL);

    SessionKeys keys;
    if (crypto_kx_client_session_keys(
            keys.rx, keys.tx,
            client_pk, client_sk, server_pk) != 0) {
        throw std::runtime_error("Handshake failed");
    }
    // Erase secret key from memory after use
    sodium_memzero(client_sk, sizeof(client_sk));
    return keys;
}


}

//both side encryption : if one side is compromised the other one may still be safe 