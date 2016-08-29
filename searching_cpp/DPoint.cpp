//#define NDEBUG

#include <random>
#include "DPoint.h"
#include "assert.h"

bool DPoint::operator<(const DPoint &p) {
    assert(this->size() == p.size());

    bool res = false;
    for (int i = 0; i < this->size(); i++){
        if (this->data()[i] < p[i]){
            res = true;
        } else if (this->data()[i] > p[i]){
            return false;
        }
    }

    return res;
}

DPoint::DPoint(std::initializer_list<double> elements) {
    for (double elem : elements){
        this->push_back(elem);
    }
}

DPoint DPoint::randomPoint(int d) {
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re(seed1);

    DPoint res;
    for (int i = 0; i < d; i++){
        res.push_back(unif(re));
    }
    return res;
}

DPoint DPoint::randomPoint_int(int d, int min, int max) {
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> uni(min,max);
    std::default_random_engine re(seed1);

    DPoint res;
    for (int i = 0; i < d; i++){
        res.push_back(uni(re));
    }
    return res;
}

bool DPoint::operator==(const DPoint &p) {
    assert(this->size() == p.size());

    for (int i = 0; i < this->size(); i++){
        if (this->data()[i] != p[i]) return false;
    }

    return true;
}

ostream &operator<<(ostream &os, const DPoint &dt) {
    for (double elem : dt){
        os << elem << ",";
    }
    return os;
}
