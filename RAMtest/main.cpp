//$t@$h
#include "RAMTester.h"
#include "MyRAMHAL.h"

int main() {
    MyRAMHAL hal;
    RAMTester tester(hal);

    tester.writePattern();
    if (!tester.verifyPattern()) {
        std::cerr << "RAM verification failed!" << std::endl;
    } else {
        std::cout << "RAM verification successful." << std::endl;
    }

    tester.boundaryStressTest();

    return 0;
}