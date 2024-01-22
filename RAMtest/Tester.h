//$t@$h
#ifndef RAMTESTER_H
#define RAMTESTER_H

#include "IRAMHAL.h"
#include <iostream>

class RAMTester {
    IRAMHAL& hal;
    static constexpr std::size_t RAM_SIZE = 65536; // Example for 64K RAM

public:
    explicit RAMTester(IRAMHAL& hal) : hal(hal) {}

    void writePattern() {
        for (std::size_t i = 0; i < RAM_SIZE; ++i) {
            hal.writeRAM(i, static_cast<uint8_t>(i & 0xFF));
        }
    }

    bool verifyPattern() {
        for (std::size_t i = 0; i < RAM_SIZE; ++i) {
            if (hal.readRAM(i) != static_cast<uint8_t>(i & 0xFF)) {
                return false; // Pattern mismatch
            }
        }
        return true;
    }

    void boundaryStressTest() {
        // Example addresses for stress test
        constexpr std::size_t addresses[] = {0x0000, 0xFFFF, 0x00FF, 0x0100, 0x5555, 0xAAAA};
        for (auto addr : addresses) {
            hal.writeRAM(addr, 0xFF);
            hal.writeRAM(addr ^ 0xFFFF, 0x00); // Complementary address
        }
    }
};

#endif // RAMTESTER_H
