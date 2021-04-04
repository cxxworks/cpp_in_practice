#include <iostream>
#include "test_util.h"
#include "printer.h"
#include "fax_machine.h"


int Test_1() {
    auto printer1 = Printer::makePrinter();
    std::cout << "printer1->getCount(): " << printer1->countObjects() << std::endl;

    auto printer2 = Printer::makePrinter();
    std::cout << "printer2->getCount(): " << printer2->countObjects() << std::endl;

    try {
        auto printer3 = Printer::makePrinter();
        std::cout << "printer3->getCount(): " << printer3->countObjects() << std::endl;
    } catch (Printer::MaxObjectsExceeded& e) {
        std::cout << "Error occurs when make printer" << std::endl;
    }
}

int Test_2() {
    auto printer = Printer::makePrinter();
    std::cout << "printer->countObjects(): " << printer->countObjects() << std::endl;

    auto fax_machine = FaxMachine::makeFaxMachine();
    std::cout << "fax_machine->getCount(): " << fax_machine->countObjects() << std::endl;

    /*
     * Printer和Machine继承同一个Counted, 共享同一个静态全局变量（Counted::numObjects）
     * 这是不符合需求的！！！
     * 
     * 应该要用基类模板来处理这个问题.
     */
    if (&printer->countObjects() == &fax_machine->countObjects()) {
        std::cout << "&printer->countObjects() is equal to &fax_machine->countObjects() !!!" << std::endl;
        std::cout << "&printer->countObjects(): " << &printer->countObjects() << std::endl;
        std::cout << "&fax_machine->countObjects(): " << &fax_machine->countObjects() << std::endl;
    }
}

int main(int argc, char** argv) {
    RUN_TEST(Test_1);
    RUN_TEST(Test_2);
}