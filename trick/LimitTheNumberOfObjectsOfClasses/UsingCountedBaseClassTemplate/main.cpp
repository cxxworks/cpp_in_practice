#include <iostream>
#include "test_util.h"
#include "printer.h"
#include "fax_machine.h"

int Test() {
    auto printer = Printer::makePrinter();
    std::cout << "printer->countObjects(): " << printer->countObjects() << std::endl;

    auto fax_machine = FaxMachine::makeFaxMachine();
    std::cout << "fax_machine->getCount(): " << fax_machine->countObjects() << std::endl;

    if (&printer->countObjects() == &fax_machine->countObjects()) {
        std::cout << "&printer->countObjects() is equal to &fax_machine->countObjects() !!!" << std::endl;
        std::cout << "&printer->countObjects(): " << &printer->countObjects() << std::endl;
        std::cout << "&fax_machine->countObjects(): " << &fax_machine->countObjects() << std::endl;
    }
}

int main(int argc, char** argv) {
    RUN_TEST(Test)
}