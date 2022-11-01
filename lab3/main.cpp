#include <iostream>
#include <functional>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

random_device rd;
mt19937 mtGenerator(rd());

class TestFunction{
private:
    class Result{
    private:
        double time, point, x, y;
    public:
        Result(double time, double point, double x, double y) : time(time), point(point), x(x), y(y) {}
        void writeResult(){
            cout<<"Total Time: "<<time<<" Point: "<<point << " X -> " << x << " Y -> " << y << endl;
        }
    };
    class Domain{
    private:
        vector<double> xDomain, yDomain;
    public:
        Domain(){};
        Domain(const vector<double> domain){
            this -> xDomain = {domain.at(0), domain.at(1)};
            this -> yDomain = {domain.at(2), domain.at(3)};
        }
        Domain(const vector<double> &xDomain, const vector<double> &yDomain) : xDomain(xDomain), yDomain(yDomain) {}
        const vector<double> &getXDomain() const {return xDomain;}
        const vector<double> &getYDomain() const {return yDomain;}
        vector<double> generateRandomPoints(){
            uniform_real_distribution<double> x_distribution(xDomain.at(0), xDomain.at(1));
            uniform_real_distribution<double> y_distribution(yDomain.at(0), yDomain.at(1));
            return {x_distribution(mtGenerator), y_distribution(mtGenerator)};
        }
    };
    vector<double> neighborFunc(vector<double> lastPoint){
    #define RANGE 0.01
        double initialFunctionResult = testFunction(lastPoint);
        if(initialFunctionResult > testFunction({lastPoint.at(0) + RANGE, lastPoint.at(1) + RANGE})) return {lastPoint.at(0) + RANGE, lastPoint.at(1) + RANGE};
        if(initialFunctionResult > testFunction({lastPoint.at(0) + RANGE, lastPoint.at(1) - RANGE})) return {lastPoint.at(0) + RANGE, lastPoint.at(1) - RANGE};
        if(initialFunctionResult > testFunction({lastPoint.at(0) - RANGE, lastPoint.at(1) + RANGE})) return {lastPoint.at(0) - RANGE, lastPoint.at(1) + RANGE};
        if(initialFunctionResult > testFunction({lastPoint.at(0) - RANGE, lastPoint.at(1) - RANGE})) return {lastPoint.at(0) - RANGE, lastPoint.at(1) - RANGE};
        return lastPoint;
    }
    double generateRandomPointInRange(vector<double> range){
        uniform_real_distribution<double> distribution(range.at(0), range.at(1));
        return distribution(mtGenerator);
    }
    function<double(vector<double>)> testFunction;
    Domain domain;
    void hillClimbChainger(vector<double>* oldPoints, vector<double> newPoints, double* initialValue, double newInitialValue){
        *oldPoints = newPoints;
        *initialValue = newInitialValue;
    }
public:
    TestFunction(){};
    TestFunction(function<double(vector<double>)> testFunction, vector<double> domain){
        this -> testFunction = testFunction;
        this -> domain = Domain(domain);
    }
    Result hillClimbing(int maxIterations = 10000){
    #define STEP 0.01
        clock_t start, end;
        start = clock();
        vector<double> randomPoints = domain.generateRandomPoints();
        vector<double> finalCoords;
        double initialValue = testFunction(randomPoints);

        for(int i = 0 ; i < maxIterations ; i++){
            if(randomPoints.at(0) >= domain.getXDomain().at(1) - STEP ||
            randomPoints.at(0) <= domain.getXDomain().at(0) + STEP ||
            randomPoints.at(1) >= domain.getYDomain().at(1) - STEP ||
            randomPoints.at(1) <= domain.getYDomain().at(0) + STEP) break;
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
        return Result(((double)(end - start)) / CLOCKS_PER_SEC, initialValue, randomPoints.at(0), randomPoints.at(1));
    }
    Result anneal(int maxIterations = 100000) {
        clock_t start, end;
        start = clock();
        vector<vector<double>> visitedPoints(2);
        visitedPoints[0] = domain.generateRandomPoints();
        for(int k = 1; k < maxIterations ; k++){
            vector<double> tkPoints = neighborFunc(visitedPoints[0]);
            if(testFunction(tkPoints) < testFunction(visitedPoints[0])) visitedPoints[1] = tkPoints;
            else{
                visitedPoints[1] = (
                        generateRandomPointInRange({0, 1}) >
                        exp(-1 * abs(testFunction(tkPoints) - testFunction(visitedPoints[0]) / (1.0 / k)))
                        ? tkPoints : visitedPoints[0]);
            }
        }
        end = clock();
        return Result(((double)(end - start)) / CLOCKS_PER_SEC,testFunction(visitedPoints[1]),visitedPoints[1].at(0),visitedPoints[1].at(1));
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
    for(int i = 0 ; i < 10 ; i++){
        testedFunctions[0].anneal().writeResult();
    }
    return 0;
}