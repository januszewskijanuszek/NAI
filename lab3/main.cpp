#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;

random_device rd;
mt19937 mt_generator(rd());

int globalIterations = 1000000;

auto brute_force = [](
        const function<double(pair<double, double>)> &f,
        const function<pair<double, double>(int, int)> &domain,
        int iterations, int a, int b) {

    auto current_p = domain(a, b);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain(a, b);
    }

    return best_point;
};

auto hill_climbing = [](
        const function<double(pair<double, double> pair)> &f,
        const function<pair<double, double>(int, int)> &start_point,
        const function<vector<pair<double, double>>(pair<double, double>, int, int)> &get_close_points,
        int max_iterations, int a, int b) {

    pair<double, double> best_p = start_point(a, b);

    for (int iteration = 0; iteration < max_iterations; iteration++) {
        auto close_points = get_close_points(best_p, a, b);
        auto best_neighbour = *min_element(
                close_points.begin(),
                close_points.end(),
                [f](auto a, auto b) {
                    return f(a) > f(b);
                }
        );

        if (f(best_neighbour) < f(best_p))
            best_p = best_neighbour;
    }
    return best_p;
};

auto simulated_annealing = [](
        const function<double(pair<double, double> pair)> &f,
        const function<pair<double, double>(int, int)> &domain,
        int iterations, int a, int b) {

    vector<pair<double, double>> pairsVector;
    uniform_real_distribution<double> uk(0, 1);
    double ukValue = uk(mt_generator);

    auto best_point = domain(a, b);
    pairsVector.push_back(best_point);

    for (int i = 0; i < iterations; ++i) {
        auto tk = domain(a, b);
        if (f(tk) <= f(best_point)) {
            best_point = tk;
            pairsVector.push_back(best_point);
        } else {
            if (ukValue < exp(-(abs(f(tk) - f(best_point)) / (1 / log(i))))) {
                best_point = tk;
                pairsVector.push_back(best_point);
            }
        }
    }

    return best_point;
};

auto xy_generator = [](int a, int b) {
    uniform_real_distribution<> dis(a, b);
    return pair<double, double>(dis(mt_generator), dis(mt_generator));
};

auto xy_generator2 = [](pair<double, double> p, int a, int b) -> vector<pair<double, double>> {
    uniform_real_distribution<> dis(a, b);
    return {pair<double, double>(dis(mt_generator), dis(mt_generator))};
};

int main() {
//    (-5;5)
    auto ackley_f = [](pair<double, double> pair) {
        return -20.0 * exp(-0.2 * sqrt(0.5 * (pow(pair.first, 2) + pow(pair.second, 2)))) -
               exp(0.5 * (cos(2 * M_PI * pair.first) + cos(2 * M_PI * pair.second))) + exp(1) + 20;
    };

//    (-5;5)
    auto himmelblau_f = [](pair<double, double> pair) {
        return pow(pow(pair.first, 2) + pair.second - 11, 2) + pow(pair.first + pow(pair.second, 2) - 7, 2);
    };

//    (-10;10)
    auto holderTable_f = [](pair<double, double> pair) {
        return -abs(sin(pair.first) * cos(pair.second) *
                    exp(abs(1 - (sqrt(pow(pair.first, 2) + pow(pair.second, 2)) / M_PI))));
    };

    cout << "----------------ackley------------------" << endl;


    auto start = std::chrono::high_resolution_clock::now();
    auto ackley_burte = brute_force(ackley_f, xy_generator, globalIterations, -5, 5);
    auto stop = std::chrono::high_resolution_clock::now();

    cout << "~brute_force~ (x,y) = " << ackley_burte.first << ", " << ackley_burte.second
         << " | result: " << ackley_f(ackley_burte)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;


    start = std::chrono::high_resolution_clock::now();
    auto ackley_hill = hill_climbing(ackley_f, xy_generator, xy_generator2, globalIterations, -5, 5);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~hill_climbing~ (x,y) = " << ackley_hill.first << ", " << ackley_hill.second
         << " | result: " << ackley_f(ackley_hill)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;


    start = std::chrono::high_resolution_clock::now();
    auto ackley_annealing = simulated_annealing(ackley_f, xy_generator, globalIterations, -5, 5);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~simulated_annealing~ (x,y) = " << ackley_annealing.first << ", " << ackley_annealing.second
         << " | result: " << ackley_f(ackley_annealing)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;

    cout << "----------------himmelblau------------------" << endl;


    start = std::chrono::high_resolution_clock::now();
    auto himmelblau_burte = brute_force(himmelblau_f, xy_generator, globalIterations, -5, 5);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~brute_force~ (x,y) = " << himmelblau_burte.first << ", " << himmelblau_burte.second
         << " | result: " << himmelblau_f(himmelblau_burte)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;


    start = std::chrono::high_resolution_clock::now();
    auto himmelblau_hill = hill_climbing(himmelblau_f, xy_generator, xy_generator2, globalIterations, -5, 5);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~hill_climbing~ (x,y) = " << himmelblau_hill.first << ", " << himmelblau_hill.second
         << " | result: " << himmelblau_f(himmelblau_hill)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;


    start = std::chrono::high_resolution_clock::now();
    auto himmelblau_annealing = simulated_annealing(himmelblau_f, xy_generator, globalIterations, -5, 5);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~simulated_annealing~ (x,y) = " << himmelblau_annealing.first << ", " << himmelblau_annealing.second
         << " | result: " << himmelblau_f(himmelblau_annealing)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;

    cout << "----------------holderTable------------------" << endl;


    start = std::chrono::high_resolution_clock::now();
    auto holderTable_burte = brute_force(holderTable_f, xy_generator, globalIterations, -10, 10);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~brute_force~ (x,y) = " << holderTable_burte.first << ", " << holderTable_burte.second
         << " | result: " << holderTable_f(holderTable_burte)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;


    start = std::chrono::high_resolution_clock::now();
    auto holderTable_hill = hill_climbing(holderTable_f, xy_generator, xy_generator2, globalIterations, -10, 10);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~hill_climbing~ (x,y) = " << holderTable_hill.first << ", " << holderTable_hill.second
         << " | result: " << holderTable_f(holderTable_hill)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;


    start = std::chrono::high_resolution_clock::now();
    auto holderTable_annealing = simulated_annealing(holderTable_f, xy_generator, globalIterations, -10, 10);
    stop = std::chrono::high_resolution_clock::now();

    cout << "~simulated_annealing~ (x,y) = " << holderTable_annealing.first << ", " << holderTable_annealing.second
         << " | result: " << holderTable_f(holderTable_annealing)
         << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
         << endl;

    return 0;
}
