//$t@$h
#ifndef MYRAMHAL_H
#define MYRAMHAL_H

#include "IRAMHAL.h"

class MyRAMHAL : public IRAMHAL {
public:
    void writeRAM(std::size_t address, uint8_t value) override {
        // *((volatile uint8_t*)address) = value;
    }

    uint8_t readRAM(std::size_t address) override {
        // return *((volatile uint8_t*)address);
        return 0; // Replace with actual read logic
    }
};

#endif // MYRAMHAL_H