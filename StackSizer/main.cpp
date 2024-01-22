//$t@$h
#include "StackTester.h"
#include "UserApplication.h"

extern "C" {
    extern uint16_t _stack_start;
    extern uint16_t _stack_end;
}

int main() {
    StackTester tester(&_stack_start, &_stack_end);

    // Call the user's application entry point
    userApplicationEntryPoint();

    std::size_t stackUsed = tester.checkUsage();
    std::cout << "Stack used: " << stackUsed << " bytes." << std::endl;

    return 0;
}