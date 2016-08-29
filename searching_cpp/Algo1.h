#ifndef SEARCHING_CPP_ALGO1_H
#define SEARCHING_CPP_ALGO1_H


#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "CBPAlgo.h"

using namespace std;

struct x_comparator {
    bool operator()(DPoint a, DPoint b) {
        return a[0] < b[0];
    }
};

struct y_comparator {
    bool operator()(DPoint a, DPoint b) {
        return a[1] < b[1];
    }
};

struct f_comparator {
    MonoFunction *f;

    f_comparator(MonoFunction *f) {
        this->f = f;
    }

    bool operator()(DPoint a, DPoint b) {
        return f->eval(a) < f->eval(b);
    }
};

class Algo1 : public CBPAlgo {

public:
    Algo1(vector<DPoint> *points, MonoFunction *f) : CBPAlgo(points, f) {}

    void run(double c) override {
        p_sort_x = new vector<DPoint>;
        copy(points->begin(), points->end(), back_inserter(*p_sort_x));
        sort(p_sort_x->begin(), p_sort_x->end(), x_comparator());
        double x1 = p_sort_x->front()[0];
        double x2 = p_sort_x->back()[0];

        p_sort_y = new vector<DPoint>;
        copy(points->begin(), points->end(), back_inserter(*p_sort_y));
        std::sort(p_sort_y->begin(), p_sort_y->end(), y_comparator());
        double y1 = p_sort_y->front()[1];
        double y2 = p_sort_y->back()[1];

        run(c, x1, x2, y1, y2);

        delete p_sort_x;
        delete p_sort_y;
    }

protected:
    vector<DPoint> *p_sort_x;
    vector<DPoint> *p_sort_y;

    void run(double c, double x1, double x2, double y1, double y2) {
        vector<DPoint> *pR_sort_x = new vector<DPoint>;
        for (DPoint p : *p_sort_x) {
            if (p[0] >= x1 && p[0] <= x2 && p[1] >= y1 && p[1] <= y2) {
                pR_sort_x->push_back(p);
            }
        }

        if (pR_sort_x->size() == 0) {
            delete pR_sort_x;
            return;
        }

//        copy(points->begin(), points->end(), back_inserter(*pR_sort_x));
//        sort(pR_sort_x->begin(), pR_sort_x->end(), x_comparator());
        DPoint median = (*pR_sort_x)[pR_sort_x->size() / 2];

        double eval = f->eval(median);
        double px = median[0];
        double py = median[1];
        double lambda, alpha, beta;

        if (eval < c) {
            (*labels)[median] = -1;

            lambda = binary_search_x_large(px + 1, x2, c, py);
            alpha = lambda == -1 ? x2 : lambda - 1;
            lambda = binary_search_y_large(py + 1, y2, c, px);
            beta = lambda == -1 ? y2 : lambda - 1;

            // Ry (R1)
            if (beta < y2) run(c, x1, px - 1, beta + 1, y2);

            // Rx (R3)
            if (alpha < x2) run(c, alpha + 1, x2, y1, py - 1);

            // Rxy (R2)
            run(c, px + 1, alpha, py + 1, beta);
        } else if (eval > c) {
            (*labels)[median] = 1;

            lambda = binary_search_x_small(x1, px - 1, c, py);
            alpha = lambda == -1 ? x1 : lambda + 1;
            lambda = binary_search_y_small(y1, py - 1, c, px);
            beta = lambda == -1 ? y1 : lambda + 1;

            // Rx
            if (alpha > x1) run (c, x1, alpha - 1, py + 1, y2);

            // Ry
            if (beta > y1) run (c, px + 1, x2, y1, beta - 1);

            // Rxy
            run(c, alpha, px - 1, beta, py - 1);
        } else {
            // assumption: no boundary point
            (*labels)[median] = 0;
        }

        delete pR_sort_x;
    }

    int binary_search_x_large(int begin, int end, double c, int py) {
        if (begin > end) {
            return -1;
        }

        int tmp = (begin + end) / 2;
        if (f->eval(tmp, py) > c) {
            int tmp2 = binary_search_x_large(begin, tmp - 1, c, py);
            return tmp2 == -1 ? tmp : tmp2;
        }
        else
            return binary_search_x_large(tmp + 1, end, c, py);
    }

    int binary_search_x_small(int begin, int end, double c, int py) {
        if (begin > end)
            return -1;

        int tmp = (begin + end) / 2;
        if (f->eval(tmp, py) < c) {
            int tmp2 = binary_search_x_small(tmp + 1, end, c, py);
            return tmp2 == -1 ? tmp : tmp2;
        }
        else
            return binary_search_x_small(begin, tmp - 1, c, py);
    }

    int binary_search_y_large(int begin, int end, double c, int px) {
        if (begin > end)
            return -1;

        int tmp = (begin + end) / 2;
        if (f->eval(px, tmp) > c) {
            int tmp2 = binary_search_y_large(begin, tmp - 1, c, px);
            return tmp2 == -1 ? tmp : tmp2;
        } else {
            return binary_search_y_large(tmp + 1, end, c, px);
        }
    }

    int binary_search_y_small(int begin, int end, double c, int px) {
        if (begin > end)
            return -1;

        int tmp = (begin + end) / 2;
        if (f->eval(px, tmp) < c) {
            int tmp2 = binary_search_y_small(tmp + 1, end, c, px);
            return tmp2 == -1 ? tmp : tmp2;
        } else {
            return binary_search_y_small(begin, tmp - 1, c, px);
        }
    }
};

#endif //SEARCHING_CPP_ALGO1_H

//    int binary_search(int begin, int end, double c, int py) {
//        if (begin == end) {
//            if (f->eval(begin, py) > c)
//                return begin;
//            else
//                return -1;
//        }
//
//        int tmp = (begin + end) / 2;
//        if (f->eval(tmp, py) > c) {
//            if (f->eval(tmp - 1, py) <= c)
//                return tmp;
//            else
//                return binary_search(begin, tmp, c, py);
//        } else {
//            if (f->eval(tmp + 1, py) > c)
//                return tmp + 1;
//            else
//                return binary_search(tmp + 1, end, c, py);
//        }
//    }