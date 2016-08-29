#ifndef SEARCHING_CPP_CBPALGO_H
#define SEARCHING_CPP_CBPALGO_H

#include <initializer_list>
#include <vector>
#include <map>
#include "DPoint.h"
#include "MonoFunction.h"
#include "assert.h"

using namespace std;

class CBPAlgo {

protected:
    vector<DPoint>* points;
    MonoFunction* f;
    map<DPoint, int>* labels;

public:
    CBPAlgo(vector<DPoint> *points, MonoFunction* f) {
        this->points = points;
        this->f = f;
        this->labels = new map<DPoint, int>;
//        for (int i = 0; i < points->size(); i++) {
//            labels->push_back(-2);
//            assert(points->at(i).size() == 2);
//        }
    }

    virtual ~CBPAlgo() {
        delete labels;
    }

    map<DPoint, int> *getLabels() const {
        return labels;
    }

    virtual void run(double c) = 0;
};


#endif //SEARCHING_CPP_CBPALGO_H
