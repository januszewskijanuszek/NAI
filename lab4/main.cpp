#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <string>
#include <functional>
#include <set>
#include <ctime>

#define INDEX_NUMBER 116

using namespace std;

random_device rd;
mt19937 mtGenerator(rd());

template<typename U>
class BitTrans{
private:
    template<typename T>
    class Parts{
    private:
        vector<bitset<INDEX_NUMBER / 4>> bitsetElements;
        vector<double> convertedValues;
    public:
        Parts<T>(){};
        Parts<T>(vector<T> bitStream){
            for(int i = 0 ; i < INDEX_NUMBER ; i += INDEX_NUMBER / 4){
                string temp;
                for(int j = 0 ; j < INDEX_NUMBER / 4 ; j++) temp += to_string(bitStream.at(j + i));
                bitsetElements.push_back(bitset<INDEX_NUMBER / 4>(temp));
                convertedValues.push_back(bitset<INDEX_NUMBER / 4>(temp).to_ullong());
            }
        }
        const vector<double> &getConvertedValues() const {return convertedValues;}
        const void toBinary(){for(bitset<INDEX_NUMBER / 4> bit : bitsetElements) cout << bit << endl;}
        const void toDecimal(){for(bitset<INDEX_NUMBER / 4> bit : bitsetElements) cout << bit.to_ullong() << endl;}
    };
    vector<U> bitStream;
    Parts<U> parts;
    double x, y;
    int index;
    static int generateRandom(){
        mt19937 rng(random_device{}());
        return uniform_int_distribution<int>{numeric_limits<U>::min(), numeric_limits<U>::max()}(rng);
    }
    static bool generateRandomBool(){
        mt19937 rng(random_device{}());
        return uniform_int_distribution<>{0, 1}(rng);
    }
public:
    static int lastIndex;
    BitTrans<U>(){
        BitTrans<U>::index = lastIndex++;
        bitStream.resize(INDEX_NUMBER);
        function<U()> tempFunc;
        const type_info &inputedType = typeid(U);
        if(*inputedType.name() == 'b') tempFunc = generateRandomBool;
        if(*inputedType.name() == 'i') tempFunc = generateRandom;
        for(int i = 0 ; i < bitStream.size() ; i++) bitStream[i] = tempFunc();
        parts = Parts<U>(bitStream);
        int mX = generateRandomBool() ? -1 : 1;
        int mY = generateRandomBool() ? -1 : 1;
        BitTrans::x = mX * parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
        BitTrans::y = mY * parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
    }
    BitTrans<U>(const vector<U> &bitStream, int index){
        BitTrans<U>::index = lastIndex++;
        if (bitStream.size() == INDEX_NUMBER){
            BitTrans::bitStream = bitStream;
            parts = Parts<U>(bitStream);
            BitTrans::x = parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
            BitTrans::y = parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
        }
        else throw out_of_range("Input should have " + to_string(INDEX_NUMBER) + " elements");
    }
    Parts<U> print(){return parts;}
    vector<double> returnVector(){return {x, y};}
    void printXandY(function<double(vector<double>)> testedFun){
        cout << " ID: " << BitTrans<U>::index << " | X -> " << x << " | Y -> " << y << " | value -> " << testedFun({x, y})<< endl;}
    int getIndex() const {return index;}
};
template<typename T>
int BitTrans<T>::lastIndex = 0;
template<typename T>
class Fitnes{
    function<double(vector<double>)> testedFunction;
    vector<BitTrans<T>> dataSet;
    static vector<BitTrans<T>> getRandomData(int amount){
        vector<BitTrans<T>> set;
        for(int i = 0 ; i < amount ; i++) set.push_back(BitTrans<T>());
        return set;
    }
public:
    explicit Fitnes<T>(int amount, function<double(vector<double>)> testedFunction){
        Fitnes<T>::dataSet = getRandomData(amount);
        Fitnes<T>::testedFunction = testedFunction;
    }
    vector<BitTrans<T>> selectStrongest(int amount){
        if(amount > dataSet.size()) throw out_of_range("Only allowed number between " + to_string(1) + " - " +
                                                               to_string(dataSet.size()));
        vector<BitTrans<T>> selection;
        vector<int> indexes;
        set<pair<double ,BitTrans<T>*>> setOfBits;
        for(int i = 0 ; i < Fitnes<T>::dataSet.size() ; i++)
            setOfBits.insert({Fitnes<T>::testedFunction(Fitnes<T>::dataSet.at(i).returnVector()), &Fitnes<T>::dataSet[i]});
        for(auto setElement = setOfBits.begin() ; 0 < amount ; amount--, setElement++)
            selection.push_back(*setElement -> second);
        return selection;
    }
    const function<double(vector<double>)> &getTestedFunction() const {return testedFunction;}
    const vector<BitTrans<T>> &getDataSet() const {return dataSet;}
};

int main(){
    clock_t start, end;
    start = clock();
    function<double(vector<double>)> boothFunction = [](const vector<double>& values){
        return pow(values.at(0) + 2 * values.at(1) - 7, 2) + pow(2 * values.at(0) + values.at(1) - 5, 2);
    };
    Fitnes<bool> fit = Fitnes<bool>(1000, boothFunction);
    fit.selectStrongest(50);
    for(BitTrans<bool> element : fit.selectStrongest(50))
        element.printXandY(fit.getTestedFunction());
    end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    return 0;
}