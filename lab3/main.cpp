#include <iostream>
#include <functional>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>
#include <map>

using namespace std;
using domain_t = vector<double>;

random_device rd;
mt19937 mtGenerator(rd());

void writeResult(vector<double> result){
    cout<<"Total Time: "<<result.at(0)<<" Point: "<<result.at(1) << " X -> " << result.at(2) << " Y -> " << result.at(3) << endl;
}

//void hillClimbChainger(vector<double>* oldPoints, vector<double> newPoints, double* initialValue, double newInitialValue){
//    *oldPoints = newPoints;
//    *initialValue = newInitialValue;
//}

// val 1 - time
// val 2 - best result
// val 3 - best x
// val 4 - best y
//vector<double> hillClimbing(function<double(vector<double>)> func, vector<double> domain, int maxIterations = 10000){
//#define STEP 0.01
//    clock_t start, end;
//    start = clock();
//
//    double x_start = domain.at(0);
//    double x_end = domain.at(1);
//    double y_start = domain.at(2);
//    double y_end = domain.at(3);
//
//    uniform_real_distribution<double> x_distribution(x_start, x_end);
//    uniform_real_distribution<double> y_distribution(y_start, y_end);
//    vector<double> randomPoints = {x_distribution(mtGenerator), y_distribution(mtGenerator)};
//    vector<double> finalCoords;
//    double initialValue = func(randomPoints);
//
//    for(int i = 0 ; i < maxIterations ; i++){
//        if(randomPoints.at(0) >= x_end - STEP || randomPoints.at(0) <= x_start + STEP || randomPoints.at(1) >= y_end - STEP || randomPoints.at(1) <= y_start + STEP) break;
//        if(func({randomPoints.at(0) + STEP, randomPoints.at(1) + STEP}) < initialValue)
//            hillClimbChainger(&randomPoints,{randomPoints.at(0) + STEP, randomPoints.at(1) + STEP},&initialValue,
//                              func({randomPoints.at(0) + STEP, randomPoints.at(1) + STEP}));
//        else if(func({randomPoints.at(0) + STEP, randomPoints.at(1) - STEP}) < initialValue)
//            hillClimbChainger(&randomPoints,{randomPoints.at(0) + STEP, randomPoints.at(1) - STEP},&initialValue,
//                              func({randomPoints.at(0) + STEP, randomPoints.at(1) - STEP}));
//        else if(func({randomPoints.at(0) - STEP, randomPoints.at(1) + STEP}) < initialValue)
//            hillClimbChainger(&randomPoints,{randomPoints.at(0) - STEP, randomPoints.at(1) + STEP},&initialValue,
//                              func({randomPoints.at(0) - STEP, randomPoints.at(1) + STEP}));
//        else if(func({randomPoints.at(0) - STEP, randomPoints.at(1) - STEP}) < initialValue)
//            hillClimbChainger(&randomPoints,{randomPoints.at(0) - STEP, randomPoints.at(1) - STEP},&initialValue,
//                              func({randomPoints.at(0) - STEP, randomPoints.at(1) - STEP}));
//    }
//    end = clock();
//    double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
//    return {totalTime, initialValue, randomPoints.at(0), randomPoints.at(1)};
//}

//void anneal(function<double(vector<double>)> function, vector<double> maxDomain, int maxIterations=1000, double step=5){
//    uniform_real_distribution<double> dist(maxDomain.at(0), maxDomain.at(1));
//    uniform_real_distribution<double> randomiserd(0, 3);
//    uniform_real_distribution<double> randomiseru(0, 1);
//    vector<double> s;
//    double x = dist(mtGenerator);
//    double y = dist(mtGenerator);
//    s.push_back(function(x,y));
//    cout<<"Starting value: ";
//    cout<<s.back()<<endl;
//    //cout<<"\nD00PA\n";
//    for(int k=1;k<maxIterations;k+=step){
//        //cout<<"\nD0"<<k<<"PA\n";
//
//        double a = neighbours(x,step, maxDomain).at(randomiserd(mtGenerator));
//        double b = neighbours(y,step, maxDomain).at(randomiserd(mtGenerator));
//        //cout<<endl<<"a:"<<a<<" b: "<<b<<endl;
//        double tempResult = function(a,b);
////        cout<<s.back()<<endl;
////        cout<<"TempResult:"<< tempResult<<endl;
//        if(tempResult<=s.back()){
////            cout<<"116\n";
//            s.push_back(tempResult);
//            x=a;
//            y=b;
//        }
//        else{
////            cout<<"122";
//            double u = randomiseru(mtGenerator);
//            double Tk = 1.0/k;
//            if( u < exp(-1*(    abs(tempResult-s.back())/Tk  ))      ){
////                cout<<"126";
//                s.push_back(tempResult);
//                x=a;
//                y=b;
//            }
//            else{
//
//            }
////            cout<<endl;
//        }
//    }
//    //cout<<"koniec\n";
//    cout<<"End value: "<<s.back()<<endl;
//}


class TestFunction{
private:
    function<double(vector<double>)> testFunction;
    vector<double> maxDomain;
    void hillClimbChainger(vector<double>* oldPoints, vector<double> newPoints, double* initialValue, double newInitialValue){
        *oldPoints = newPoints;
        *initialValue = newInitialValue;
    }
public:
    TestFunction(){};
    TestFunction(function<double(vector<double>)> testFunction, vector<double> maxDomain){
        this -> testFunction = testFunction;
        this -> maxDomain = maxDomain;
    }
    vector<double> hillClimbing(int maxIterations = 10000){
    #define STEP 0.01
        clock_t start, end;
        start = clock();

        double x_start = maxDomain.at(0);
        double x_end = maxDomain.at(1);
        double y_start = maxDomain.at(2);
        double y_end = maxDomain.at(3);

        uniform_real_distribution<double> x_distribution(x_start, x_end);
        uniform_real_distribution<double> y_distribution(y_start, y_end);
        vector<double> randomPoints = {x_distribution(mtGenerator), y_distribution(mtGenerator)};
        vector<double> finalCoords;
        double initialValue = testFunction(randomPoints);

        for(int i = 0 ; i < maxIterations ; i++){
            if(randomPoints.at(0) >= x_end - STEP || randomPoints.at(0) <= x_start + STEP || randomPoints.at(1) >= y_end - STEP || randomPoints.at(1) <= y_start + STEP) break;
            if(testFunction({randomPoints.at(0) + STEP, randomPoints.at(1) + STEP}) < initialValue)
                hillClimbChainger(&randomPoints,{randomPoints.at(0) + STEP, randomPoints.at(1) + STEP},&initialValue,
                                  testFunction({randomPoints.at(0) + STEP, randomPoints.at(1) + STEP}));
            else if(testFunction({randomPoints.at(0) + STEP, randomPoints.at(1) - STEP}) < initialValue)
                hillClimbChainger(&randomPoints,{randomPoints.at(0) + STEP, randomPoints.at(1) - STEP},&initialValue,
                                  testFunction({randomPoints.at(0) + STEP, randomPoints.at(1) - STEP}));
            else if(testFunction({randomPoints.at(0) - STEP, randomPoints.at(1) + STEP}) < initialValue)
                hillClimbChainger(&randomPoints,{randomPoints.at(0) - STEP, randomPoints.at(1) + STEP},&initialValue,
                                  testFunction({randomPoints.at(0) - STEP, randomPoints.at(1) + STEP}));
            else if(testFunction({randomPoints.at(0) - STEP, randomPoints.at(1) - STEP}) < initialValue)
                hillClimbChainger(&randomPoints,{randomPoints.at(0) - STEP, randomPoints.at(1) - STEP},&initialValue,
                                  testFunction({randomPoints.at(0) - STEP, randomPoints.at(1) - STEP}));
        }
        end = clock();
        double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        return {totalTime, initialValue, randomPoints.at(0), randomPoints.at(1)};
    }

    const function<double(vector<double>)> &getTestFunction() const {
        return testFunction;
    }
    const vector<double> &getMaxDomain() const {
        return maxDomain;
    }
};


int main(int argc, char** argv) {
#define AMOUNT_OF_FUNTIONS 3
    vector<double> domain;
    vector<TestFunction> testedFunctions(AMOUNT_OF_FUNTIONS);
    // Goldstein–Price function
    testedFunctions[0] = TestFunction([](const vector<double>& values){
        for(double d : values) if(-2 > d || d > 2) throw invalid_argument("Input must be between -2 and 2");
        return  (1 + pow(values.at(0) + values.at(1) + 1, 2) * (19 - 14 * values.at(0) + 3 * pow(values.at(0), 2)
                 - 14 * values.at(1) + 6 * values.at(0) * values.at(1) + 3 * pow(values.at(1), 2))) *
                (30 + pow(2 * values.at(0) - 3 * values.at(1),2) *
                      (18 - 32 * values.at(0) + 12 * pow(values.at(0), 2) + 48 * values.at(1)
                       - 36 * values.at(0) * values.at(1) + 27 * pow(values.at(1), 2)));
    }, {-2, 2, -2, 2});
    // Himmelblau's function
    testedFunctions[1] = TestFunction([](const vector<double>& values) {
        for(double d : values) if(-5 > d || d > 5) throw invalid_argument("Input must be between -2 and 2");
        return pow(pow(values.at(0),2)+values.at(1)-11,2) + pow(values.at(0)+pow(values.at(1),2)-7,2);
    }, {-5, 5, -5, 5});
    testedFunctions[2] = TestFunction([](const vector<double>& values){
        for(double d : values) if(-10 > d || d > 10) throw invalid_argument("Input must be between -10 and 10");
        return pow(values.at(0) + 2 * values.at(1) - 7, 2) + pow(2 * values.at(0) + values.at(1) - 5, 2);
    }, {-10, 10, -10, 10});
    for(int i = 0 ; i < 1000 ; i++){
        writeResult(testedFunctions[0].hillClimbing());
    }
//    for(TestFunction funcClass : testedFunctions){
//        cout << "siema";
//    }
    return 0;
}