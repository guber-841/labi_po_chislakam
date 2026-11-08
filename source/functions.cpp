#include "functions.h"
#include "classes.h"

#include <cmath>

double func(double x){
    return log(1 + pow(x, 2.0)); // сама функция, которую мы и апроксимируем 
}

double coef_m(int n, double* values_x, double k){ //рассчет коэфицентов m k-ое
    double sum = 0.0;
    for(int i = 0; i < n; i++){
        sum += pow(values_x[i], k);
    }
    return sum/n;
}

double coef_K(int n, double* values_x, double* values_function, double k){ // рассчет коэфицентов K i-ое
    double sum = 0.0;
    for(int i = 0; i < n; i++){
        sum += pow(values_x[i], k)*values_function[i];
    }
    return sum/n;
}

double Approx::func(double x){ // сам апроксимирующий полином
    return coef[0] + coef[1]*x + coef[2]*pow(x, 2.0);
}

void Approx::settup(int n, double* values_x, double* values_function){ // расчет корней по формуле из учебнка, я вообще хз как они эту формулу получают, тем более что у них там опечатка. я не знаю линал помогите 
    double s12 = coef_m(n, values_x, 1.0);
    double s13 = coef_m(n, values_x, 2.0);
    double m3 = coef_m(n, values_x, 3.0);
    double m4 = coef_m(n, values_x, 4.0);
    double s22 = sqrt(s13 - pow(s12, 2.0));
    double s23 = (m3 - s12*s13)/s22;
    double s33 = sqrt(m4 - pow(s13, 2.0) - pow(s23, 2.0));
    double z1 = coef_K(n, values_x, values_function, 0.0);
    double z2 = (coef_K(n, values_x, values_function, 1.0) - s12*z1)/s22;
    double z3 = (coef_K(n, values_x, values_function, 2.0) - s13*z1 - s23*z2)/s33;
    coef[2] = z3/s33;
    coef[1] = (z2-s23*coef[2])/s22;
    coef[0] = z1 - s12*coef[1] - s13*coef[2];
}