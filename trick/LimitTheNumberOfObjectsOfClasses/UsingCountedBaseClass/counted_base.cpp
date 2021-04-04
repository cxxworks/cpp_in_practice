#include <iostream>
#include "counted_base.h"

Counted::Counted() {
    init();
}

Counted::Counted(const Counted& rhs) {
    init();
}

Counted::~Counted() {
    numObjects--;
}

const int& Counted::countObjects() {
    return numObjects;
}

void Counted::init() {
    if (numObjects >= kMaxObjects) {
        throw MaxObjectsExceeded();
    } else {
        numObjects++;
    }
}

const int Counted::kMaxObjects = 2;
int Counted::numObjects = 0;