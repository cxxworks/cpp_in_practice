#ifndef PRINTER_H
#define PRINTER_H

#include <memory>
#include "counted_base.h"

class Printer: private Counted { // 通过private继承，隐藏Base的protected成员
public:
    ~Printer();

    using Counted::countObjects;
    using Counted::MaxObjectsExceeded;

    static std::shared_ptr<Printer> makePrinter();
    static std::shared_ptr<Printer> makePrinter(const Printer& rhs);

private:
    Printer();
    Printer(const Printer& rhs);
};

#endif