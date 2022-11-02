#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <string>

#define INDEX_NUMBER 116

using namespace std;

random_device rd;
mt19937 mtGenerator(rd());

class BitTrans{
private:
    class Parts{
    private:
        vector<bitset<INDEX_NUMBER / 4>> bitsetElements;
        vector<double> convertedValues;
    public:
        Parts(){};
        Parts(vector<bool> bitStream){
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
    vector<bool> bitStream;
    Parts parts;
    double x, y;
    bool generateRandomBool(){
        mt19937 rng(random_device{}());
        return uniform_int_distribution<>{0, 1}(rng);
    }
public:
    BitTrans(){
        bitStream.resize(INDEX_NUMBER);
        for(int i = 0 ; i < bitStream.size() ; i++) bitStream[i] = generateRandomBool();
        parts = Parts(bitStream);
        this -> x = parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
        this -> y = parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
    }
    BitTrans(const vector<bool> &bitStream){
        if (bitStream.size() == INDEX_NUMBER){
            this->bitStream = bitStream;
            parts = Parts(bitStream);
            this -> x = parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
            this -> y = parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
        }
        else throw out_of_range("Number should have exacly 164 bits");
    }
    Parts print(){return parts;}
    void printXandY(){cout << "X -> " << x << " | Y -> " << y << endl;}
};

int main(){
    BitTrans gene;
    gene.print().toBinary();
    gene.print().toDecimal();
    gene.printXandY();
    return 0;
}