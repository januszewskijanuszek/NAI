#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <string>
#include <random>
#include <limits.h>

using namespace std;
using dVector = vector<double>;

#define AMOUNT_OF_PROBES 100

// Rand devices declaration
random_device randomDevice;
mt19937 mtGenerator(randomDevice());

void domainInputValidator(dVector domain){
    for(int i = 0 ; true ; i = i + 2){
        try{
            if(domain.at(i) > domain.at(i + 1)) throw invalid_argument("First goes smaller argument!");
        } catch (out_of_range e){ break;}
    }
}

dVector randomProbing(const function<double(dVector)>& testedFunction, dVector domain, int iteracions){
    double x_start = domain.at(0);
    double x_end = domain.at(1);
    double y_start = domain.at(2);
    double y_end = domain.at(3);
    for(int i = 0 ; i < iteracions ; i++){
        uniform_real_distribution<double> x_distribution(x_start, x_end);
        uniform_real_distribution<double> y_distribution(y_start, y_end);
    }
    vector<double> siema;
    return siema;
}

int main(int argc, char** argv){
    vector<string> rawArgs(argv, argc + argv);
    dVector domain;
    for(int i = 2 ; i < argc ; i++) domain.push_back(stod(rawArgs.at(i)));
    map<string, function<double(dVector)>> funcMap;
    funcMap["bea"] = [](const dVector& values){
        for(double d : values) if(-4.5 > d || d > 4.5) throw invalid_argument("Input must be between -4.5 and 4.5");
        return pow(1.5 - values.at(0) + values.at(0) * values.at(1), 2) +
               pow(2.25 - values.at(0) + values.at(0) * pow(values.at(1), 2),2) +
               pow(2.625 - values.at(0) + values.at(0) *  pow(values.at(1), 3), 2);;
    };
    funcMap["gold"] = [](const dVector& values){
        for(double d : values) if(-2 > d || d > 2) throw invalid_argument("Input must be between -2 and 2");
        return  (1 + pow(values.at(0) + values.at(1) + 1, 2) * (19 - 14 * values.at(0) + 3 * pow(values.at(0), 2)
                - 14 * values.at(1) + 6 * values.at(0) * values.at(1) + 3 * pow(values.at(1), 2))) *
                (30 + pow(2 * values.at(0) - 3 * values.at(1),2) *
                (18 - 32 * values.at(0) + 12 * pow(values.at(0), 2) + 48 * values.at(1)
                - 36 * values.at(0) * values.at(1) + 27 * pow(values.at(1), 2)));
    };
    funcMap["booth"] = [](const dVector& values){
        for(double d : values) if(-10 > d || d > 10) throw invalid_argument("Input must be between -10 and 10");
        return pow(values.at(0) + 2 * values.at(1) - 7, 2) + pow(2 * values.at(0) + values.at(1) - 5, 2);
    };
    cout << funcMap[rawArgs.at(1)](domain);
    return 0;
}