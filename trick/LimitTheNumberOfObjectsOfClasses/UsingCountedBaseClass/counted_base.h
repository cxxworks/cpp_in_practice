#ifndef COUNTED_BASE_H
#define COUNTED_BASE_H

class Counted {
public:
    class MaxObjectsExceeded {};

    static const int& countObjects();

protected:
    Counted();
    Counted(const Counted& rhs);

    ~Counted();

private:
    static const int kMaxObjects;
    static int numObjects;
    void init();
};

#endif