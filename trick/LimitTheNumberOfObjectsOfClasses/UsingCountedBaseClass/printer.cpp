#include <iostream>
#include "printer.h"

Printer::Printer() {
    std::cout << "Printer::Printer" << std::endl;
}

Printer::Printer(const Printer& rhs) {
    std::cout << "Printer::Printer" << std::endl;
}

Printer::~Printer() {
    std::cout << "Printer::~Printer" << std::endl;
}

std::shared_ptr<Printer> Printer::makePrinter() {
    // return std::make_shared<Printer>();  // 错误: 因为Printer::Printer()声明为private, 阻止std::make_shared隐式调用构造函数
    return std::shared_ptr<Printer>(new Printer());
}

std::shared_ptr<Printer> Printer::makePrinter(const Printer& rhs) {
    // return std::make_shared<Printer>(rhs);  // 错误: 因为Printer::Printer(const Printer& rhs)声明为private, 阻止std::make_shared隐式调用构造函数
    return std::shared_ptr<Printer>(new Printer(rhs));
}