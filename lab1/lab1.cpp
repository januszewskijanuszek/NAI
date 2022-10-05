#include <iostream>
#include <map>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#define ERROR_CODE 1
#define OK 0

using namespace std;

using myMap = map<string, string>;
// double(double)
// 1 wychodzi
// 2, ... wchodzi
using oneElementFunction = function<double(double)>;
using doubleElementFunction = function<double(int, int)>;

void errorMessage(){
    cout << "lab1 [FUNCTION] [ARG...]\n";
    cout << "FUNCTION\n";
    cout << "sin - sinus\n";
    cout << "add - add\n";
    cout << "mod - modulo\n";
    exit(ERROR_CODE);
}

void printOne(double value, oneElementFunction func){
    cout << func(value);
}

int main(int argc, char** argv) {
    map<string, oneElementFunction> oneFormat;
    map<string, doubleElementFunction> twoFormat;
    if(argc == 3){
        oneFormat["sin"] = [](double x){return sin(x);};
        int value = stod(*(argv + 2));
        printOne(value, oneFormat.at(*(argv + 1)));
    } else if(argc == 4){
        twoFormat["add"] = [](int x, int y){return x + y;};
        twoFormat["mod"] = [](int x, int y){return x % y;};
    } else{
        errorMessage();
    }
    return OK;
}
