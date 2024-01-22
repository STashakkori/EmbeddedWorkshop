// $t@$h
#ifndef ISRECORDREADER_H
#define ISRECORDREADER_H

#include <vector>

enum srec_type_t {
    SREC_TYPE_S1, SREC_TYPE_S2, SREC_TYPE_S3,
    SREC_TYPE_S7, SREC_TYPE_S9
};

struct SRecord {
    srec_type_t type;
    int len;
    unsigned long addr;
    std::vector<char> data;
};

class ISRecordReader {
public:
    virtual bool readSRecord(SRecord& record) = 0;
    virtual ~ISRecordReader() = default;
};

#endif // ISRECORDREADER_H
