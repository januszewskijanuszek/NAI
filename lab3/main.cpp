#include <iostream>
#include <functional>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>
#include <map>

using namespace std;
using domain_t = std::vector<double>;

std::random_device rd;
std::mt19937 mt_generator(rd());

void writeOutResults(double time, double result){
    using namespace std;
    cout<<"\nTime: "<<time<<" Result: "<<result;
}

vector<double> neighbours(double a, double step, auto domain){
    vector<double> result;
    result.push_back(a);
    if(a-step>domain.at(0))result.push_back(a-step);
    else result.push_back(a);
    if(a+step<domain.at(1))result.push_back(a+step);
    else result.push_back(a);
    return result;
}

void climb(auto function, auto domain, int maxIterations=1000, double step=1){

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    std::uniform_real_distribution<double> dist(domain.at(0), domain.at(1));

    double result;
    double x = dist(mt_generator);
    double y = dist(mt_generator);
    result = function(x,y);
    //cout<<"Initial result:"<<result<<endl;
    double best=result;
    int flag;

    for(int i=0;i<maxIterations;i++){
        vector<double> a = neighbours(x,step, domain);
        vector<double> b = neighbours(y,step, domain);
        double temp1=function(a.at(1),b.at(1));
        if(result>temp1){
            result = temp1;
            x=a.at(1);
            y=b.at(1);
        }
        double temp2=function(a.at(1),b.at(2));
        if(result>temp2){
            result = temp2;
            x=a.at(1);
            y=b.at(2);
        }
        double temp3=function(a.at(2),b.at(1));
        if(result>temp3){
            result = temp3;
            x=a.at(2);
            y=b.at(1);
        }
        double temp4=function(a.at(2),b.at(2));
        if(result>temp4){
            result = temp4;
            x=a.at(2);
            y=b.at(2);
        }
        double temp5=function(a.at(1),b.at(0));
        if(result>temp5){
            result = temp5;
            x=a.at(1);
        }
        double temp6=function(a.at(0),b.at(1));
        if(result>temp6){
            result = temp6;
            y=b.at(1);
        }
        double temp7=function(a.at(2),b.at(0));
        if(result>temp7){
            result = temp7;
            x=a.at(2);
        }
        double temp8=function(a.at(0),b.at(2));
        if(result>temp8){
            result = temp8;
            y=b.at(2);
        }
        if(result==best){
            break;
        }
        best = result;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeOutResults(cpu_time_used,best);
}

void anneal(auto function, auto domain, int maxIterations=1000, double step=5){
    std::uniform_real_distribution<double> dist(domain.at(0), domain.at(1));
    std::uniform_real_distribution<double> randomiserd(0, 3);
    std::uniform_real_distribution<double> randomiseru(0, 1);
    vector<double> s;
    double x = dist(mt_generator);
    double y = dist(mt_generator);
    s.push_back(function(x,y));
    cout<<"Starting value: ";
    cout<<s.back()<<endl;
    //cout<<"\nD00PA\n";
    for(int k=1;k<maxIterations;k+=step){
        //cout<<"\nD0"<<k<<"PA\n";

        double a = neighbours(x,step, domain).at(randomiserd(mt_generator));
        double b = neighbours(y,step, domain).at(randomiserd(mt_generator));
        //cout<<endl<<"a:"<<a<<" b: "<<b<<endl;
        double tempResult = function(a,b);
//        cout<<s.back()<<endl;
//        cout<<"TempResult:"<< tempResult<<endl;
        if(tempResult<=s.back()){
//            cout<<"116\n";
            s.push_back(tempResult);
            x=a;
            y=b;
        }
        else{
//            cout<<"122";
            double u = randomiseru(mt_generator);
            double Tk = 1.0/k;
            if( u < exp(-1*(    abs(tempResult-s.back())/Tk  ))      ){
//                cout<<"126";
                s.push_back(tempResult);
                x=a;
                y=b;
            }
            else{

            }
//            cout<<endl;
        }
    }
    //cout<<"koniec\n";
    cout<<"End value: "<<s.back()<<endl;
}



int main(int argc, char** argv) {
    vector<string> input(argv, argc + argv);
    map<string, function<double(vector<double>)>> funcMap;
    funcMap["gold"] = [](const vector<double>& values){
        for(double d : values) if(-2 > d || d > 2) throw invalid_argument("Input must be between -2 and 2");
        return  (1 + pow(values.at(0) + values.at(1) + 1, 2) * (19 - 14 * values.at(0) + 3 * pow(values.at(0), 2)
                - 14 * values.at(1) + 6 * values.at(0) * values.at(1) + 3 * pow(values.at(1), 2))) *
                (30 + pow(2 * values.at(0) - 3 * values.at(1),2) *
                (18 - 32 * values.at(0) + 12 * pow(values.at(0), 2) + 48 * values.at(1)
                - 36 * values.at(0) * values.at(1) + 27 * pow(values.at(1), 2)));
    };
    funcMap["himmel"] = [](const vector<double>& values) {
        return pow(pow(values.at(0),2)+values.at(1)-11,2) + pow(values.at(0)+pow(values.at(1),2)-7,2);
    };
    vector<double> domain={-4.5,4.5};
    cout<<"Climb:";
    for(int i=0;i<5;i++){
        climb(beal_f,domain,1000000);
    }
    cout<<"\nAnneal:\n";
    for(int i=0;i<5;i++){
        anneal(beal_f,domain,1000000,1.5);
    }

    return 0;
}