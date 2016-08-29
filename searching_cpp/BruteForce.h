#ifndef SEARCHING_CPP_BRUTEFORCE_H
#define SEARCHING_CPP_BRUTEFORCE_H


#include "CBPAlgo.h"

class BruteForce : public CBPAlgo{
public:
    BruteForce(vector<DPoint> *points, MonoFunction *f) : CBPAlgo(points, f) {}

    void run(double c) override {
        for (int i = 0; i < points->size(); i ++){
            double val = f->eval(points->at(i));
            if (val < c) {
                (*labels)[(*points)[i]] = -1;
            } else if (val > c) {
                (*labels)[(*points)[i]] = 1;
            } else {
                (*labels)[(*points)[i]] = 0;
            }
        }
    }
};


#endif //SEARCHING_CPP_BRUTEFORCE_H
