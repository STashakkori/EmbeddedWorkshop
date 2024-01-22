//$t@$h
#ifndef SRECORDPROCESSOR_H
#define SRECORDPROCESSOR_H

#include "ISRecordReader.h"
#include <iostream>
#include <cstring>

typedef void (*entrypoint_t)(void);

class SRecordProcessor {
    ISRecordReader& reader;
    char programmer_buf[8192];
    entrypoint_t entrypoint = nullptr;

public:
    explicit SRecordProcessor(ISRecordReader& reader) : reader(reader) {}

    void process() {
        SRecord record;

        while (reader.readSRecord(record)) {
            if (record.addr + record.len > sizeof(programmer_buf)) {
                std::cerr << "Error: Address out of bounds." << std::endl;
                continue;
            }

            switch (record.type) {
                case SREC_TYPE_S1:
                case SREC_TYPE_S2:
                case SREC_TYPE_S3:
                    std::memcpy(programmer_buf + record.addr, record.data.data(), record.len);
                    break;
                case SREC_TYPE_S7:
                    entrypoint = reinterpret_cast<entrypoint_t>(reinterpret_cast<long>(programmer_buf + record.addr));
                    break;
                case SREC_TYPE_S9:
                    if (entrypoint != nullptr) {
                        entrypoint();
                    } else {
                        std::cerr << "Error: Entry point not set." << std::endl;
                    }
                    return;
            }
        }
    }
};

#endif // SRECORDPROCESSOR_H