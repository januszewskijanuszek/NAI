#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <string>

using namespace std;
using dVector = vector<double>;

int main(int argc, char** argv){
    vector<string> rawArgs(argv, argc + argv);
    dVector domain = {stod(rawArgs.at(2)), stod(rawArgs.at(3))};
    map<string, function<double(dVector)>> funcMap;
    funcMap["bea"] = [](const dVector& values){
        for(double d : values) if(-4.5 > d || d > 4.5) throw invalid_argument("Domain must be between -4.5 and 4.5");
        return pow(1.5 - values.at(0) + values.at(0) * values.at(1), 2) +
               pow(2.25 - values.at(0) + values.at(0) * pow(values.at(1), 2),2) +
               pow(2.625 - values.at(0) + values.at(0) *  pow(values.at(1), 3), 2);;
    };
    cout << funcMap[rawArgs.at(1)](domain);
    return 0;
}