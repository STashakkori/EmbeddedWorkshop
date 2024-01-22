//$t@$h
#ifndef SRECORDREADER_H
#define SRECORDREADER_H

#include "ISRecordReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

class SRecordReader : public ISRecordReader {
    std::ifstream file;

    int hexCharToInt(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return 10 + c - 'A';
        if (c >= 'a' && c <= 'f') return 10 + c - 'a';
        throw std::invalid_argument("Invalid hex character");
    }

    unsigned char hexPairToChar(const std::string& hex) {
        return static_cast<unsigned char>((hexCharToInt(hex[0]) << 4) + hexCharToInt(hex[1]));
    }

    bool validateChecksum(const std::string& line, int byteCount) {
        int sum = 0;
        for (int i = 0; i < byteCount * 2; i += 2) {
            sum += hexPairToChar(line.substr(2 + i, 2));
        }
        sum = (~sum) & 0xFF;
        return sum == hexPairToChar(line.substr(2 + byteCount * 2, 2));
    }

    bool parseLine(const std::string& line, SRecord& record) {
        if (line[0] != 'S') return false;

        record.type = static_cast<srec_type_t>(line[1] - '0');
        int byteCount = hexPairToChar(line.substr(2, 2));
        int addressLength = (record.type == SREC_TYPE_S1 ? 4 : (record.type == SREC_TYPE_S2 ? 6 : 8));
        record.addr = std::stoul(line.substr(4, addressLength), nullptr, 16);

        int dataLength = byteCount * 2 - addressLength - 4;  // 4 for type and byte count
        record.data.clear();
        for (int i = 0; i < dataLength; i += 2) {
            record.data.push_back(hexPairToChar(line.substr(4 + addressLength + i, 2)));
        }

        if (!validateChecksum(line, byteCount)) {
            throw std::runtime_error("Invalid checksum in S-record");
        }

        return true;
    }

public:
    explicit SRecordReader(const std::string& filename) : file(filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    bool readSRecord(SRecord& record) override {
        std::string line;
        if (std::getline(file, line)) {
            return parseLine(line, record);
        }
        return false;
    }
};

#endif // SRECORDREADER_H