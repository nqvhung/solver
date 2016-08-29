#ifndef SEARCHING_CPP_MAX_H
#define SEARCHING_CPP_MAX_H


#include "MonoFunction.h"

class Max : public MonoFunction{
public:
    Max() : MonoFunction() {}

    Max(int m) : MonoFunction(m) {}

    DPoint map(DPoint p) override {
        double max = 0;

        for (double d : p){
            max = std::max(max, d);
        }

        DPoint res;
        for (int i = 0; i < m; i++){
            res.push_back(max);
        }
        return res;
    }

    double eval(DPoint p) override {
        double max = 0;

        for (double d : p){
            max = std::max(max, d);
        }

        return max;
    }

    double eval(double x, double y) override {
        return std::max(x,y);
    }
};


#endif //SEARCHING_CPP_MAX_H
