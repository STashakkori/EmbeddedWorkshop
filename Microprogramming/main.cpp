//$t@$h
// QVLx Labs 2024
#include "SRecordReader.h"
#include "SRecordProcessor.h"

void entrypoint_function() {
    std::cout << "Entrypoint function executed." << std::endl;
}

int main() {
    try {
        SRecordReader sRecordReader("path_to_srecord_file.srec");
        SRecordProcessor processor(sRecordReader);

        processor.process();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}