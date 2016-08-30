#include <iostream>
#include "DPoint.h"
#include "MonoFunction.h"
#include "Sum.h"
#include "Max.h"
#include "CBPAlgo.h"
#include "BruteForce.h"
#include "Algo1.h"
#include "Algo2.h"
#include "FunctionCounter.h"

using namespace std;

int my_main1(){
    int n = 10;
    int d = 3;
    int m = 2;
    std::vector<DPoint> points;
    for (int i = 0; i < n; i++) {
        points.push_back(DPoint::randomPoint(d));
    }

//    for (DPoint point : points) {
//        std::cout << point << endl;
//    }

//    MonoFunction* f = new Sum(m);
    MonoFunction *f = new Max(m);
    DPoint delta1 = DPoint({0, 0});
    DPoint delta2 = DPoint({1, 1});

    std::vector<DPoint> satisfies;
    for (DPoint point : points) {
        DPoint output = f->map(point);
        if (output > delta1 && output < delta2) {
            satisfies.push_back(point);
        }
    }

    for (DPoint point : satisfies) {
        std::cout << point << endl;
    }

    delete f;

    return 0;
}

int my_main2(){
    int n = 10;
    int d = 2;
    vector<DPoint>* points = new vector<DPoint>;
    for (int i = 0; i < n; i++) {
        points->push_back(DPoint::randomPoint(d));
    }

//    MonoFunction* f = new Sum;
    MonoFunction *f = new Max;
    double c = 0.5;

    CBPAlgo* algo = new BruteForce(points, f);
    algo->run(c);
    for (auto i : *algo->getLabels()){
        std::cout << i.first << "\t" << i.second << endl;
    }

    delete f;
    delete algo;

    return 0;
}

int my_main3(){
    int n = 1000000;
    int d = 2;
    vector<DPoint>* points = new vector<DPoint>;
    for (int i = 0; i < n; i++) {
        points->push_back(DPoint::randomPoint_int(d, 0, 10));
    }

//    MonoFunction* f = new Sum;
    MonoFunction *f = new Max;
    double c = 5.5;

//    CBPAlgo* algo = new BruteForce(points, f);
//    CBPAlgo* algo = new Algo1(points, f);
    CBPAlgo* algo = new Algo2(points, f);
    algo->run(c);
    for (auto i : *algo->getLabels()){
        std::cout << i.first << "\t" << i.second << endl;
    }

    delete f;
    delete algo;

    return 0;
}

int my_main4(){
    int n = 10000;
    int d = 2;
    vector<DPoint>* points = new vector<DPoint>;
    for (int i = 0; i < n; i++) {
        points->push_back(DPoint::randomPoint_int(d, 0, 10000000));
    }

//    MonoFunction* f = new Sum;
    MonoFunction *f = new Max;
    double c = 5.5;

    FunctionCounter* counter1 = new FunctionCounter(f);
    CBPAlgo* bf = new BruteForce(points, counter1);

    FunctionCounter* counter2 = new FunctionCounter(f);
//    CBPAlgo* algo = new Algo1(points, f);
//    CBPAlgo* algo = new Algo2(points, f);
    CBPAlgo* algo = new Algo2(points, counter2);

    algo->run(c);
    for (auto i : *algo->getLabels()){
        std::cout << i.first << "\t" << i.second << endl;
    }

    bf->run(c);
    bool correct = true;
    for (auto i : *algo->getLabels()){
        auto j = bf->getLabels()->find(i.first);
        if (j == bf->getLabels()->end()) {
            correct = false;
            break;
        } else if (i.second != j->second) {
            correct = false;
            break;
        }
    }

    std::cout << std::boolalpha << "Correctness: " << correct << endl;
    std::cout << "Baseline: " << counter1->getCount() << "\t" << counter1->getCacheSize() << endl;
    std::cout << "Algo: " << counter2->getCount() << "\t" << counter2->getCacheSize() << endl;

    delete f;
    delete counter1;
    delete counter2;
    delete algo;
    delete bf;

    return 0;
}


int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return my_main1();
//    return my_main2();
//    return my_main3();
    return my_main4();
}