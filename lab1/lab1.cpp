#include <iostream>
#include <map>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#define ERROR_CODE 1
#define OK 0

using namespace std;

using predefinedFunction = function<double(vector<double>)>;

void errorMessage(){
    cout << "lab1 [FUNCTION] [ARG...]\n";
    cout << "FUNCTION\n";
    cout << "sin - sinus - takes only one arg\n";
    cout << "add - add - takes two\n";
    cout << "mod - modulo - takes two\n";
    exit(ERROR_CODE);
}

int main(int argc, char** argv) {
    map<string, predefinedFunction> functionMap;
    vector<string> args(argv, argc + argv);
    vector<double> doubleArgs;
    for(int i = 2 ; true ; i++){
        try{
            doubleArgs.push_back(stod(args.at(i)));
        } catch(out_of_range e){break;}
    }
    functionMap["add"] = [](vector<double> x){double sum = 0;for(double value : x){sum += value;}return sum;};
    functionMap["mod"] = [](vector<double> x){double sum = 0;for(int i = 0 ; i < 2 ; i++){sum += x.at(i);}return sum;};
    functionMap["sin"] = [](vector<double> x){return sin(x.at(0));};
    try{
        cout << functionMap[args.at(1)](doubleArgs) << endl;
    }
    catch(out_of_range e){errorMessage();}
    catch(bad_function_call e){errorMessage();}
    return OK;
}
