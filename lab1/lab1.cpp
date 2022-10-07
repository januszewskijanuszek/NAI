#include <iostream>
#include <map>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#define ERROR_CODE 1
#define OK 0

using namespace std;

// double(double)
// 1 output
// 2, ... input
using oneElementFunction = function<double(double)>;
using twoElementFunction = function<double(int, int)>;

void errorMessage(){
    cout << "lab1 [FUNCTION] [ARG...]\n";
    cout << "FUNCTION\n";
    cout << "sin - sinus\n";
    cout << "add - add\n";
    cout << "mod - modulo\n";
    exit(ERROR_CODE);
}

void printOne(double value, oneElementFunction function){
    cout << function(value);
}

void printTwo(int parameterOne, int parameterTwo, twoElementFunction function){
    cout << function(parameterOne, parameterTwo);
}

int main(int argc, char** argv) {
    map<string, oneElementFunction> oneFormat;
    map<string, twoElementFunction> twoFormat;
    if(argc == 3){
        oneFormat["sin"] = [](double x){return sin(x);};
        vector<string> inputArgs(argv, argv + argc);
        // k -> you can chose what function you want to call by (k) key
        try{
            printOne(
                    stod(inputArgs.at(2)),
                    oneFormat.at(inputArgs.at(1)));
        } catch (out_of_range e){ errorMessage();}
    } else if(argc == 4){
        twoFormat["add"] = [](int x, int y){return x + y;};
        twoFormat["mod"] = [](int x, int y){return x % y;};
        vector<string> inputArgs(argv, argv + argc);
        try {
            printTwo(
                    stoi(inputArgs.at(2)),
                    stoi(inputArgs.at(3)),
                    twoFormat.at(inputArgs.at(1)));
        } catch (out_of_range e){ errorMessage();}
    } else{
        errorMessage();
    }
    return OK;
}
