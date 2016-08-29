#ifndef SEARCHING_CPP_MONFUNCTION_H
#define SEARCHING_CPP_MONFUNCTION_H


#include "DPoint.h"

class MonoFunction {
protected:
    int m = 0;

public:
    MonoFunction() {}

    MonoFunction(int m) {
        this->m = m;
    }

    virtual ~MonoFunction() {

    }

    virtual double eval(DPoint p) = 0;
    virtual double eval(double x, double y) = 0;
    virtual DPoint map(DPoint p) = 0;
};


#endif //SEARCHING_CPP_MONFUNCTION_H
