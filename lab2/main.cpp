#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <string>
#include <random>

using namespace std;
using dVector = vector<double>;

#define AMOUNT_OF_PROBES 10

// Rand devices declaration
random_device randomDevice;
mt19937 mtGenerator(randomDevice());

void domainInputValidator(dVector domain){
    for(int i = 0 ; true ; i = i + 2){
        try{
            domain.at(i) > domain.at(i + 1) ? throw invalid_argument("First goes smaller argument!") : 0;
        } catch (out_of_range e){ break;}
    }
}

void printResult(dVector result){
    cout << "Smallest value: " << result.at(0) << endl;
    cout << "X = " << result.at(1) << endl;
    cout << "Y = " << result.at(2) << endl;
}

dVector randomProbing(const function<double(dVector)>& testedFunction, dVector domain, int iteracions){
    double x_start = domain.at(0);
    double x_end = domain.at(1);
    double y_start = domain.at(2);
    double y_end = domain.at(3);
    dVector smallestValues(3);
    smallestValues[0] = numeric_limits<double>::max();
    for(int i = 0 ; i < iteracions ; i++){
        dVector radomPoints(2);
        uniform_real_distribution<double> x_distribution(x_start, x_end);
        uniform_real_distribution<double> y_distribution(y_start, y_end);
        radomPoints[0] = x_distribution(mtGenerator);
        radomPoints[1] = y_distribution(mtGenerator);
        double temp = testedFunction(radomPoints);
        if(smallestValues[0] > temp){
            smallestValues[0] = temp;
            smallestValues[1] = radomPoints.at(0);
            smallestValues[2] = radomPoints.at(1);
        }
    }
    return smallestValues;
}

int main(int argc, char** argv){
    vector<string> rawArgs(argv, argc + argv);
    dVector domain;
    try {for (int i = 2; i < argc; i++) domain.push_back(stod(rawArgs.at(i)));
    }catch (exception e){throw invalid_argument("Input must be a number!");}
    domainInputValidator(domain);
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
    printResult(randomProbing(funcMap[rawArgs.at(1)], domain, AMOUNT_OF_PROBES));
    for(int j = 1;j < 1000000; j = j * 10) {
        double sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += randomProbing(funcMap[rawArgs.at(1)], domain, AMOUNT_OF_PROBES*j).at(0);
        }
        cout << 10*j <<" 20 avg: " << sum / 20.0 << endl;
    }
    return 0;
}