#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <string>
#include <functional>

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
    static int generateRandom(){
        mt19937 rng(random_device{}());
        return uniform_int_distribution<int>{numeric_limits<U>::min(), numeric_limits<U>::max()}(rng);
    }
    static bool generateRandomBool(){
        mt19937 rng(random_device{}());
        return uniform_int_distribution<>{0, 1}(rng);
    }
public:
    BitTrans<U>(){
        bitStream.resize(INDEX_NUMBER);
        function<U()> tempFunc;
        const type_info &inputedType = typeid(U);
        if(*inputedType.name() == 'b') tempFunc = generateRandomBool;
        if(*inputedType.name() == 'i') tempFunc = generateRandom;
        for(int i = 0 ; i < bitStream.size() ; i++) bitStream[i] = tempFunc();
        parts = Parts<U>(bitStream);
        BitTrans::x = parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
        BitTrans::y = parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
    }
    BitTrans<U>(const vector<U> &bitStream){
        if (bitStream.size() == INDEX_NUMBER){
            BitTrans::bitStream = bitStream;
            parts = Parts<U>(bitStream);
            BitTrans::x = parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
            BitTrans::y = parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
        }
        else throw out_of_range("Input should have " + to_string(INDEX_NUMBER) + " elements");
    }
    Parts<U> print(){return parts;}
    void printXandY(){cout << "X -> " << x << " | Y -> " << y << endl;}
};

int main(){
    BitTrans<bool> gene;
    gene.printXandY();
    return 0;
}