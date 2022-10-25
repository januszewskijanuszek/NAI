#include <iostream>
#include <functional>
#include <vector>

domain_t tabu_method(
        const std::function<double(domain_t)> &f, domain_t start_point,
        std::function<std::vector<domain_t>(domain_t)> get_close_points,
        int max_iterations) {
    using namespace std;
    domain_t best_point = start_point;
    list<domain_t> tabu_list = {start_point};
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        cout << iteration << " " << tabu_list.back() << " " << f(tabu_list.back())
             << endl;
        for (auto tabu_i = tabu_list.rbegin(); tabu_i != tabu_list.rend();
             tabu_i++) {
            auto close_points_all = get_close_points(*tabu_i);
            vector<domain_t> close_points;
            copy_if(close_points_all.begin(), close_points_all.end(),
                    back_inserter(close_points), [&](auto p) {
                        return !count(tabu_list.begin(), tabu_list.end(), p);
                    });
            if (close_points.size() != 0) {
                tabu_list.push_back(
                        *min_element(close_points.begin(), close_points.end(),
                                     [f](auto a, auto b) { return f(a) < f(b); }));
                break;
            }
        }
        if (f(best_point) > f(tabu_list.back())) best_point = tabu_list.back();
    }
    return best_point;
}