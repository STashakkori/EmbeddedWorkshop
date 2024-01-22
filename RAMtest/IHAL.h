//$t@$h
#ifndef IRAMHAL_H
#define IRAMHAL_H

#include <cstddef>
#include <cstdint>

class IRAMHAL {
public:
    virtual void writeRAM(std::size_t address, uint8_t value) = 0;
    virtual uint8_t readRAM(std::size_t address) = 0;
    virtual ~IRAMHAL() = default;
};

#endif // IRAMHAL_H