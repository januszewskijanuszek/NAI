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
    dVector doubleArgv = {stod(rawArgs.at(2)), stod(rawArgs.at(3))};
    map<string, function<double(dVector)>> funcMap;

    funcMap["bae"] = [](const vector<double>& values){
        for(double d : values){
            cout << d << endl;
        }
        return 0.0;
    };
    funcMap[rawArgs.at(1)](doubleArgv);
    return 0;
}