/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../library.hpp"


// Class with getted data from somewhere
class GetPacket {
 private:
    #if (USE_WINSOCK)
    // Address, from which
    sockaddr_in srcAddress;
    int srcAddressLength = sizeof(sockaddr_in);
    // Data, contained in this array
    char buffer[100];
    int length = 0;
    // Offeset of current reading caret
    int offset = 0;
    #endif  // (USE_WINSOCK)

 public:
    // Winsock special functions
    #if (USE_WINSOCK)
    // Function to try get new data from net
    GetPacket* tryGetData(const SOCKET winSocket);
    const sockaddr_in* getSourceAddress() const;
    int getSourceAddressLength() const;
    #endif

    // Function for check, if has enought bytes to read
    bool isBytesAvaliable(int bytes) const;
    // Returns length of getted data
    int getLength() const;
    // Functions for get data from message by order
    //template <typename T>
    //T getData() const;
    // Functions for get data from message at specified position
    template <typename T>
    T getData(int offset) const;
    const void* getPointer() const;
};


/*template <typename T>
T GetPacket::getData() const {
    #if (CHECK_CORRECTION)
    if (offset + sizeof(T) > length) {
        logImportant("Can't read data - not enogh length");
    }
    #endif

    // Moving caret for reading next object correct
    offset += sizeof(T);
    // Reading current object (without added offset)
    return readNet((T)(buffer[offset-sizeof(T)]));
}*/

template <typename T>
T GetPacket::getData(int _offset) const {
    #if (CHECK_CORRECTION)
    if (_offset + sizeof(T) > length) {
        logImportant("Can't read data - not enogh length");
    }
    #endif
    return readNet((T)(buffer[_offset]));
}
