//
// Created by Thanh Tam Nguyen on 29/08/16.
//

#ifndef SEARCHING_CPP_ALGO2_H
#define SEARCHING_CPP_ALGO2_H


#include "CBPAlgo.h"
#include "Algo1.h"

using namespace std;

class Algo2 : public CBPAlgo {

public:
    Algo2(vector<DPoint> *points, MonoFunction *f) : CBPAlgo(points, f) {}

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
        vector<DPoint> *pR = new vector<DPoint>;
        for (DPoint p : *p_sort_x) {
            if (p[0] >= x1 && p[0] <= x2 && p[1] >= y1 && p[1] <= y2) {
                pR->push_back(p);
            }
        }

        if (pR->empty()) {
            delete pR;
            return;
        }

        DPoint median = (*pR)[pR->size() / 2];
        double eval = f->eval(median);
        double px = median[0];
        double py = median[1];
        double lambda, alpha, beta;

        if (eval < c) {
            (*labels)[median] = -1;

            // Set beta
            vector<double> *Y1 = new vector<double>;
            for (DPoint p : *p_sort_y) {
                if (p[0] >= x1 && p[0] <= x2 && p[1] >= y1 && p[1] <= y2)
                    if (p[0] >= x1 && p[0] <= px - 1 && p[1] >= py + 1 && p[1] <= y2)
                        Y1->push_back(p[1]);
            }
            if (Y1->empty() || f->eval(px, Y1->back()) < c) {
                beta = y2;
            } else {
                lambda = (*Y1)[binary_search_y_large(Y1, 0, Y1->size() - 1, c, px)];
                beta = lambda - 1;
                assert(lambda != -1);
            }

            // Set alpha
            vector<double> *X2 = new vector<double>;
            for (DPoint p : *p_sort_x) {
                if (p[0] >= x1 && p[0] <= x2 && p[1] >= y1 && p[1] <= y2)
                    if (p[0] >= px + 1 && p[0] <= x2 && p[1] >= y1 && p[1] <= py - 1)
                        X2->push_back(p[0]);
            }
            if (X2->empty() || f->eval(X2->back(), py) < c) {
                alpha = x2;
            } else {
                lambda = (*X2)[binary_search_x_large(X2, 0, X2->size() - 1, c, py)];
                alpha = lambda - 1;
                assert(lambda != -1);
            }

            // Ry (R1)
            if (beta < y2) run(c, x1, px - 1, beta + 1, Y1->back());

            // Rxy (R2)
            run(c, px + 1, alpha, py + 1, beta);

            // Rx (R3)
            if (alpha < x2) run(c, alpha + 1, X2->back(), y1, py - 1);

            delete Y1;
            delete X2;
        } else if (eval > c) {
            (*labels)[median] = 1;

            // Set alpha
            vector<double> *Xalpha = new vector<double>;
            for (DPoint p : *p_sort_x) {
                if (p[0] >= x1 && p[0] <= x2 && p[1] >= y1 && p[1] <= y2)
                    if (p[0] >= x1 && p[0] <= px - 1 && p[1] >= py + 1 && p[1] <= y2)
                        Xalpha->push_back(p[0]);
            }
            if (Xalpha->empty() || f->eval(Xalpha->front(), py) > c) {
                alpha = x1;
            } else {
                lambda = binary_search_x_small(Xalpha, 0, Xalpha->size() - 1, c, py);
                alpha = lambda + 1;
                assert(lambda != -1);
            }

            // Set beta
            vector<double> *Ybeta = new vector<double>;
            for (DPoint p : *p_sort_y) {
                if (p[0] >= x1 && p[0] <= x2 && p[1] >= y1 && p[1] <= y2)
                    if (p[0] >= px + 1 && p[0] <= x2 && p[1] >= y1 && p[1] <= py - 1)
                        Ybeta->push_back(p[1]);
            }
            if (Ybeta->empty() || f->eval(px, Ybeta->front()) > c) {
                beta = y1;
            } else {
                lambda = binary_search_y_small(Ybeta, 0, Ybeta->size() - 1, c, px);
                beta = lambda + 1;
                assert(lambda != -1);
            }

            // Rx
            if (alpha > x1) run(c, Xalpha->front(), alpha - 1, py + 1, y2);

            // Rxy
            run(c, alpha, px -1, beta, py -1);

            // Ry
            if (beta > y1) run(c, px + 1, x2, Ybeta->front(), beta - 1);

            delete Xalpha;
            delete Ybeta;
        } else {
            // assumption: no boundary point
            (*labels)[median] = 0;
        }

        delete pR;
    }

    int binary_search_x_small(vector<double> *x_sort, int begin, int end, double c, double py) {
        if (begin > end) return -1;

        int tmp = (begin + end) / 2;
        if (f->eval((*x_sort)[tmp], py) < c) {
            int tmp2 = binary_search_x_small(x_sort, tmp + 1, end, c, py);
            return tmp2 == -1 ? tmp : tmp2;
        } else {
            return binary_search_x_small(x_sort, begin, tmp - 1, c, py);
        }
    }

    int binary_search_x_large(vector<double> *x_sort, int begin, int end, double c, double py) {
        if (begin > end) return -1;

        int tmp = (begin + end) / 2;
        if (f->eval((*x_sort)[tmp], py) > c) {
            int tmp2 = binary_search_x_large(x_sort, begin, tmp - 1, c, py);
            return tmp2 == -1 ? tmp : tmp2;
        } else {
            return binary_search_x_large(x_sort, tmp + 1, end, c, py);
        }
    }

    int binary_search_y_small(vector<double> *y_sort, int begin, int end, double c, double px) {
        if (begin > end) return -1;

        int tmp = (begin + end) / 2;
        if (f->eval(px, (*y_sort)[tmp]) < c) {
            int tmp2 = binary_search_y_small(y_sort, tmp + 1, end, c, px);
            return tmp2 == -1 ? tmp : tmp2;
        } else {
            return binary_search_y_small(y_sort, begin, tmp - 1, c, px);
        }
    }

    int binary_search_y_large(vector<double> *y_sort, int begin, int end, double c, double px) {
        if (begin > end) return -1;

        int tmp = (begin + end) / 2;
        if (f->eval(px, (*y_sort)[tmp]) > c) {
            int tmp2 = binary_search_y_large(y_sort, begin, tmp - 1, c, px);
            return tmp2 == -1 ? tmp : tmp2;
        } else {
            return binary_search_y_large(y_sort, tmp + 1, end, c, px);
        }
    }
};


#endif //SEARCHING_CPP_ALGO2_H
