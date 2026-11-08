#ifndef CLASSES_H
#define CLASSES_H

class Approx {
public:
    double coef[3];

    double func(double x);
    void settup(int n, double* values_x, double* values_function);
};

#endif