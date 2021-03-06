#ifndef FAX_MACHINE_H
#define FAX_MACHINE_H

#include <memory>
#include "counted_base.h"

class FaxMachine: private Counted { // 通过private继承，隐藏Base的protected成员
public:
    ~FaxMachine();

    using Counted::countObjects;
    using Counted::MaxObjectsExceeded;

    static std::shared_ptr<FaxMachine> makeFaxMachine();
    static std::shared_ptr<FaxMachine> makeFaxMachine(const FaxMachine& rhs);

private:
    FaxMachine();
    FaxMachine(const FaxMachine& rhs);
};

#endif