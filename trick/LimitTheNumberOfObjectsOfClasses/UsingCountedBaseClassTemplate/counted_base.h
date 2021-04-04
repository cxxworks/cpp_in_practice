#ifndef COUNTED_BASE_H
#define COUNTED_BASE_H

template<typename BeingCounted>
class Counted {
public:
    class MaxObjectsExceeded {};

    static const int& countObjects() {
        return numObjects;
    }

protected:
    Counted(){
        init();
    }

    Counted(const Counted& rhs) {
        init();
    }

    ~Counted() {
        numObjects--;
    }

private:
    static const int kMaxObjects;
    static int numObjects;
    
    void init() {
        if (numObjects >= kMaxObjects) {
            throw MaxObjectsExceeded();
        } else {
            numObjects++;
        }
    }
};

#endif