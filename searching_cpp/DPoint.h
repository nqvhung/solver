#ifndef SEARCHING_CPP_DPOINT_H
#define SEARCHING_CPP_DPOINT_H


#include <initializer_list>
#include <vector>
using namespace std;

class DPoint : public std::vector<double>{

public:
    static DPoint randomPoint(int d);
    static DPoint randomPoint_int(int d, int min, int max);

    DPoint(std::initializer_list<double> elements);
    DPoint() : std::vector<double>() {}

    bool operator<(const DPoint& p);
    bool operator==(const DPoint& p);
    friend ostream& operator<<(ostream& os, const DPoint& dt);
};


#endif //SEARCHING_CPP_DPOINT_H
