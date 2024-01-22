//$t@$h
#ifndef STACKTESTER_H
#define STACKTESTER_H

#include <cstdint>
#include <iostream>

class StackTester {
    uint16_t* stackStart;
    uint16_t* stackEnd;
    uint16_t pattern;

public:
    StackTester(uint16_t* start, uint16_t* end, uint16_t pattern = 0xDEAD) 
        : stackStart(start), stackEnd(end), pattern(pattern) {
        fillPattern();
    }

    void fillPattern() {
        for (uint16_t* ptr = stackStart; ptr < stackEnd; ++ptr) {
            *ptr = pattern;
        }
    }

    std::size_t checkUsage() {
        std::size_t used = 0;
        for (uint16_t* ptr = stackStart; ptr < stackEnd; ++ptr, ++used) {
            if (*ptr != pattern) {
                break;
            }
        }
        return used * sizeof(uint16_t);
    }
};

#endif // STACKTESTER_H