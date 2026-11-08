#include <iostream>
#include <cstdlib> // system
#include <cmath>
#include <iomanip> // чтобы вывод красивый был
#include <fstream> // чтобы с файлами рабоать 

#include "functions.h"
#include "classes.h"

using namespace std;

int main(){
    int n; // chislo tochek
    cout << "chislo tochek" << endl;
    cin >> n;
    n = n + 1;
    Approx approx;

    double* values_x = new double[n]; // массив точек по иксу
    double* values_function = new double[n]; // массив истиных значений 
    double* values_approx = new double[n]; // массив значений апроксимации
    double* values_fault = new double[n]; // массив ошибок апроксимации

    // заполнение массивов
    for(int i = 0; i<n; i++){
        values_x[i] = i*(1.0/(n-1));
        values_function[i] = func(values_x[i]);
    }

    approx.settup(n, values_x, values_function); // задаем коэфиценты в полиноме

    // заполнение масссива с ошибками и подсчет погрешностей 
    double epsilon_max = 0.0;
    double fault_squared_sum = 0.0;
    for(int i = 0; i<n; i++){
        values_approx[i] = approx.func(values_x[i]);
        values_fault[i] = abs(values_approx[i] - values_function[i]);
        if (values_fault[i] >= epsilon_max){
            epsilon_max = values_fault[i];
        }
        fault_squared_sum += pow(values_fault[i], 2.0);
    }

    double epsilon_sqared = fault_squared_sum/n;
    double epsilon_m = sqrt(epsilon_sqared);

    //вывод всего этого говна в файлы и консоль
    const int width = 16;

    // обзываем файлы
    ofstream alldata("database/all_values.dat");
    ofstream true_func("database/func_values.dat");
    ofstream aprx_func("database/aprx_values.dat");

    // устанавливаем вывод
    alldata << scientific << setprecision(6);
    true_func << scientific << setprecision(6);
    aprx_func << scientific << setprecision(6);

    // запись этого бедлама в файл и консоль
    cout << right << setw(width) << "x" << setw(width) << "y" << setw(width) << "phi" << setw(width) << "epsilon" << endl;
    alldata << right << setw(width) << "x" << setw(width) << "y" << setw(width) << "phi" << setw(width) << "epsilon" << endl;
    true_func << right << setw(width) << "x" << setw(width) << "y" << endl;
    aprx_func << right << setw(width) << "x" << setw(width) << "y" << endl;
    for(int i = 0; i<n; i++) {
        cout << right << setw(width) << values_x[i] << setw(width) << values_function[i] << setw(width) << values_approx[i] << setw(width) << values_fault[i] << endl;
        alldata << right << setw(width) << values_x[i] << setw(width) << values_function[i] << setw(width) << values_approx[i] << setw(width) << values_fault[i] << endl;
        true_func << right << setw(width) << values_x[i] << setw(width) << values_function[i] << endl;
        aprx_func << right << setw(width) << values_x[i] << setw(width) << values_approx[i] << endl;
    }

    // закрытие файлов в которые писали
    alldata.close();
    true_func.close();
    aprx_func.close();

    /* Мы любим чудеса и яркие картинки,
    Вот рыжая лиса и розовые свинки.
    Волшебный мир друзьями наполнится опять,
    Придумаем мы сами — давайте рисовать!
    Придумаем мы сами — давайте рисовать! */
    system("gnuplot plots/plot.gp");

    // вывод того что просит лаба
    cout <<  "maksimalnaya lazja: " << setw(width) << epsilon_max << endl;
    cout <<  "sredniy kvadrat lazji: " << setw(width) << epsilon_sqared << endl;
    cout << "sredne-kvadratichnaya lazja: " << setw(width) << epsilon_m << endl;
    cout << "koeficenti v polynome c 1 po 3: " << setw(width) << approx.coef[0] << "\t" << setw(width) << approx.coef[1] << "\t" << setw(width) << approx.coef[2] << endl;

    delete[] values_x;
    delete[] values_function;
    delete[] values_approx;
    delete[] values_fault;

    return 0;
}