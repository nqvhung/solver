//
// Created by Thanh Tam Nguyen on 30/08/16.
//

#ifndef SEARCHING_CPP_FUNCTIONCOUNTER_H
#define SEARCHING_CPP_FUNCTIONCOUNTER_H


#include "MonoFunction.h"
#include <unordered_map>

using namespace std;

class FunctionCounter : public MonoFunction {

private:
    MonoFunction *f;
    unordered_map<DPoint, double> cache;
    int count;

public:
    FunctionCounter(MonoFunction *f) {
        this->f = f;
        count = 0;
    }

    double eval(DPoint p) override {
        count++;
        if (cache.find(p) == cache.end()) {
            cache[p] = f->eval(p);
        }
        return cache[p];
    }

    double eval(double x, double y) override {
        count++;
        DPoint p = DPoint({x,y});

        if (cache.find(p) == cache.end()) {
            cache[p] = f->eval(p);
        }
        return cache[p];
    }

    DPoint map(DPoint p) override {
        return p;
    }

    int getCount() const {
        return count;
    }

    int getCacheSize() const {
        return cache.size();
    }
};


#endif //SEARCHING_CPP_FUNCTIONCOUNTER_H
