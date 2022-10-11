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
    cout << "sin - sinus - takes only one arg\n";
    cout << "add - add - takes two\n";
    cout << "mod - modulo - takes two\n";
    exit(ERROR_CODE);
}

int main(int argc, char** argv) {
    map<string, oneElementFunction> oneFormat;
    map<string, twoElementFunction> twoFormat;
    if(argc == 3){
        oneFormat["sin"] = [](double x){return sin(x);};
        vector<string> inputArgs(argv, argv + argc);
        // k -> you can chose what function you want to call by (k) key
        try{
            cout << oneFormat[inputArgs.at(1)](
                    stoi(inputArgs.at(2))) << endl;
        }
        catch (out_of_range e){ errorMessage();}
        catch (bad_function_call e){ errorMessage();}
    } else if(argc == 4){
        twoFormat["add"] = [](int x, int y){return x + y;};
        twoFormat["mod"] = [](int x, int y){return x % y;};
        vector<string> inputArgs(argv, argv + argc);
        try {
            cout << twoFormat[inputArgs.at(1)](
                    stoi(inputArgs.at(2)),
                    stoi(inputArgs.at(3))) << endl;
        }
        catch (bad_function_call e){ errorMessage();}
        catch (out_of_range e){ errorMessage();}
    } else{
        errorMessage();
    }
    return OK;
}
