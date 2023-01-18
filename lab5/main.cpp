#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <bitset>

#define INDEX_NUMBER 116

using namespace std;

random_device rd;
mt19937 mt_generator(rd());

class Chromosome{
private:
    // Class special designed for encoding end decoding digits
    class Parts{
    private:
        vector<bool> bitStream;
        vector<bitset<INDEX_NUMBER / 4>> bitsetElements;
        vector<double> convertedValues; // 4 elements vector that include all parts of the class
    public:
        Parts(){};
        // Inputs a set of bits [1001010110010] in vector and translate it to bitset
        // At the end you can use toBinary and toDecimal method that allows you to display them
        Parts(vector<bool> bitStream){
            Parts::bitStream = bitStream;
            for(int i = 0 ; i < INDEX_NUMBER ; i += INDEX_NUMBER / 4){
                string temp;
                for(int j = 0 ; j < INDEX_NUMBER / 4 ; j++) temp += to_string(bitStream.at(j + i));
                bitsetElements.push_back(bitset<INDEX_NUMBER / 4>(temp));
                convertedValues.push_back(bitset<INDEX_NUMBER / 4>(temp).to_ullong());
            }
        }
        const vector<bool> &getBitStream() const {return bitStream;}
        const vector<double> &getConvertedValues() const {return convertedValues;}
        const void toBinary(){for(bitset<INDEX_NUMBER / 4> bit : bitsetElements) cout << bit << endl;}
        const void toDecimal(){for(bitset<INDEX_NUMBER / 4> bit : bitsetElements) cout << bit.to_ullong() << endl;}
    }; // End of Parts
    vector<bool> bitStream;
    Parts parts;
    double x, y;
    pair<int, int> factors;
    double fitnessValue;
    static double boothFunc(pair<double, double> pair){
        return pow(pair.first + 2 * pair.second - 7, 2) + pow(2 * pair.first + pair.second - 5, 2);
    }
public:
    Chromosome(){
        bitStream.resize(INDEX_NUMBER); // Setting new size of bitstream
        for(int i = 0 ; i < bitStream.size() ; i++) bitStream[i] = generateRandomBool(); // Implementing a new bite
        Chromosome::parts = Parts(bitStream);
        factors.first = generateRandomBool() ? -1 : 1;
        factors.second = generateRandomBool() ? -1 : 1;
        // The secret of creating Chromosome is here -> take first part and devide it by second
        Chromosome::x = Chromosome::factors.first * parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
        Chromosome::y = Chromosome::factors.second * parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
        Chromosome::fitnessValue = boothFunc(make_pair(x, y));
    }
    Chromosome(const vector<bool> &bitStream, pair<int, int> factors){
        Chromosome::factors = factors;
        if (bitStream.size() == INDEX_NUMBER){
            Chromosome::bitStream = bitStream;
            parts = Parts(bitStream);
            Chromosome::x = factors.first * parts.getConvertedValues().at(0) / (parts.getConvertedValues().at(1) / INDEX_NUMBER);
            Chromosome::y = factors.second * parts.getConvertedValues().at(2) / (parts.getConvertedValues().at(3) / INDEX_NUMBER);
            Chromosome::fitnessValue = boothFunc(make_pair(x, y));
        }
        else throw out_of_range("Input should have " + to_string(INDEX_NUMBER) + " elements");
    }
    static bool generateRandomBool(){
        mt19937 rng(random_device{}());
        return uniform_int_distribution<>{0, 1}(rng);
    }
    const pair<int, int> &getFactors() const {return factors;}
    Parts print(){return parts;}
    vector<double> returnVector(){return {x, y};}
    double getFitnessValue() const {return fitnessValue;}
    void printXandY(){
        cout << " | X -> " << x << " | Y -> " << y << " |  Val -> "<< fitnessValue << endl;}
};
class Mutation{
private:
    Chromosome labChromosome;
    static vector<Chromosome> selectRandomFromGroup(vector<Chromosome> group, int amount){
        vector<Chromosome> qualified(amount);
        vector<int> picked(amount);
        for(int i = 0 ; i < amount ; i++){
            int randomId = uniform_int_distribution<int>(1, group.size())(mt_generator) - 1;
            auto element = find(picked.begin(), picked.end(), randomId);
            if(element != picked.end()){
                i --;
                continue;
            } else{
                picked[i] = randomId;
                qualified[i] = group[randomId];
            }
        }
        return qualified;
    }
public:
    Mutation(const Chromosome &labChromosome) : labChromosome(labChromosome) {}

    void printState(string messgae, Chromosome mutated){
        cout << endl << messgae << endl;
        labChromosome.printXandY();
        mutated.printXandY();
        cout << "-----------------------" << endl;
    }

    Chromosome onePointMutation(){
        int point = uniform_int_distribution<int> (0, INDEX_NUMBER - 1)(mt_generator);
        vector<bool> chaingedChromosome = labChromosome.print().getBitStream();
        chaingedChromosome[point] = !chaingedChromosome[point];
        return Chromosome(chaingedChromosome, labChromosome.getFactors());
    }
    Chromosome multiPointMutation(int pointsToMutate){
        vector<bool> chaingedChromosome = labChromosome.print().getBitStream();
        for (int i = 0; i < pointsToMutate; ++i) {
            int point = uniform_int_distribution<int> (0, INDEX_NUMBER - 1)(mt_generator);
            chaingedChromosome[point] = !chaingedChromosome[point];
        }
        return Chromosome(chaingedChromosome, labChromosome.getFactors());
    }
    Chromosome uniformMutation(double rate){
        vector<bool> chaingedChromosome = labChromosome.print().getBitStream();
        for (int i = 0; i < INDEX_NUMBER ; ++i) {
            if (std::uniform_real_distribution<double> (0, 1)(mt_generator) < rate) chaingedChromosome[i] = !chaingedChromosome[i];
        }
        return Chromosome(chaingedChromosome, labChromosome.getFactors());
    }
    Chromosome crossover(){
        vector<bool> parent2(INDEX_NUMBER);
        for (int i = 0; i < INDEX_NUMBER; ++i) parent2[i] = Chromosome::generateRandomBool();
        int point = uniform_int_distribution<int> (0, INDEX_NUMBER - 1)(mt_generator);
        vector<bool> child;
        vector<bool> temp = labChromosome.print().getBitStream();
        child.insert(child.end(), temp.begin(), temp.begin() + point);
        child.insert(child.end(), parent2.begin() + point, parent2.end());
        return Chromosome(child, labChromosome.getFactors());
    }
    Chromosome twoPointCrossover(){
        vector<bool> parent2(INDEX_NUMBER);
        for (int i = 0; i < INDEX_NUMBER; ++i) parent2[i] = Chromosome::generateRandomBool();
        pair<int, int> points;
        int point1 = uniform_int_distribution<int> (0, INDEX_NUMBER - 1)(mt_generator);
        int point2 = uniform_int_distribution<int> (0, INDEX_NUMBER - 1)(mt_generator);
        if(point1 > point2) swap(point1, point2);
        vector<bool> child;
        vector<bool> iHaveToSaveThisToThisVectorBecauseIDontKnowWhyItDoesNotWorkInNormalWay = labChromosome.print().getBitStream();
        child.insert(child.end(),
                     iHaveToSaveThisToThisVectorBecauseIDontKnowWhyItDoesNotWorkInNormalWay.begin(),
                     iHaveToSaveThisToThisVectorBecauseIDontKnowWhyItDoesNotWorkInNormalWay.begin() + point1);
        child.insert(child.end(), parent2.begin() + point1, parent2.begin() + point2);
        child.insert(child.end(),
                     iHaveToSaveThisToThisVectorBecauseIDontKnowWhyItDoesNotWorkInNormalWay.begin() + point2,
                     iHaveToSaveThisToThisVectorBecauseIDontKnowWhyItDoesNotWorkInNormalWay.end());
        return Chromosome(child, labChromosome.getFactors());
    }
    static Chromosome rouletteWheelSelection(int size){
        cout << "Roulette Wheel Selection" << endl;
        vector<Chromosome> crowd(size);
        for (int i = 0 ; i < size ; i++) {
            crowd[i] = Chromosome();
            crowd[i].printXandY();
        }
        double fitnessSummary = 0;
        for(Chromosome c : crowd) fitnessSummary += c.getFitnessValue();
        uniform_real_distribution<double> distribution(0, fitnessSummary);
        double randomPic = distribution(mt_generator);
        double sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += crowd[i].getFitnessValue();
            if(sum > randomPic) return crowd[i];
        }
        return crowd[0];
    }
    static vector<Chromosome> tournamentSelection(int popSize, int tournaments, int groupSize){
        cout << "Tournament Selection" << endl;
        vector<Chromosome> victorious(tournaments);
        vector<Chromosome> crowd(popSize);
        for (int i = 0 ; i < popSize ; i++) {
            crowd[i] = Chromosome();
            crowd[i].printXandY();
        }
        cout << " ------------------ " << endl;
        for(int i = 0 ; i < tournaments ; i++){
            vector<Chromosome> group = selectRandomFromGroup(crowd, groupSize);
            Chromosome best = group[0];
            for(Chromosome c: group) if(c.getFitnessValue() < best.getFitnessValue()) best = c;
            victorious[i] = best;
        }
        return victorious;
    }
};

int main(){
    Chromosome labChromosome = Chromosome();
    Mutation mutation = Mutation(labChromosome);
    // Lab chromosome always first
    mutation.printState("One point mutation", mutation.onePointMutation());
    mutation.printState("Multi point mutation", mutation.multiPointMutation(5));
    mutation.printState("Uniform mutation", mutation.uniformMutation(0.5));
    mutation.printState("Crossover", mutation.crossover());
    mutation.printState("Two Point Crossover", mutation.twoPointCrossover());
    Mutation::rouletteWheelSelection(10).printXandY();
    for(Chromosome chromosome : Mutation::tournamentSelection(10, 3, 3)) chromosome.printXandY();
    return 0;
}