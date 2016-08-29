#ifndef SEARCHING_CPP_SUM_H
#define SEARCHING_CPP_SUM_H


#include "MonoFunction.h"

class Sum : public MonoFunction {
public:
    Sum() : MonoFunction() {}

    Sum(int m) : MonoFunction(m) {}

    DPoint map(DPoint p) override {
        double sum = 0;

        for (double d : p){
            sum += d;
        }

        DPoint res;
        for (int i = 0; i < m; i++){
            res.push_back(sum);
        }
        return res;
    }

    virtual double eval(DPoint p) override {
        double sum = 0;

        for (double d : p){
            sum += d;
        }

        return sum;
    }

    virtual double eval(double x, double y) override {
        return x + y;
    }
};


#endif //SEARCHING_CPP_SUM_H
