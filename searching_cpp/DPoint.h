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

namespace std {
    template <> struct hash<DPoint>
    {
        size_t operator()(const DPoint &p) const
        {
            size_t res = 1;
            for (double coordinate : p) {
                res = res * 51 + hash<double>()(coordinate);
            }
            return res;
            //            return (51 + hash<double>()(p[0])) * 51 + hash<double>()(p[1]);
            /* your code here, e.g. "return hash<int>()(x.value);" */
        }
    };
}


#endif //SEARCHING_CPP_DPOINT_H
