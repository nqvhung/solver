#ifndef SEARCHING_CPP_AVERAGE_H
#define SEARCHING_CPP_AVERAGE_H


#include "Sum.h"

class Average : public Sum {
public:
    Average() : Sum() {}
    Average(int m) : Sum(m) {}

    DPoint map(DPoint p) {
        DPoint sum = Sum::map(p);
        for (int i = 0; i < sum.size(); i++){
            sum[i] = sum[i] / (double) p.size();
        }
        return sum;
    }

    double eval(DPoint p) {
        double sum = Sum::eval(p);
        return sum / (double) p.size();
    }

    double eval(double x, double y){
        return (x + y) / 2;
    }
};


#endif //SEARCHING_CPP_AVERAGE_H
