#ifndef ARGCV_ML_SGD_HH
#define ARGCV_ML_SGD_HH

// Gradient Descent
// Gradient Descent is a first-order optimization algorithm. 
// To find a local minimum of a function using gradient descent, 
// one takes steps proportional to the negative of the gradient 
// (or of the approximate gradient) of the function at the 
// current point.

// Stochastic Gradient Descent 
// Stochastic gradient descent is a gradient descent optimization 
// method for minimizing an objective function that is written as 
// a sum of differentiable functions.

#include <cstdio>
#include <cstdint>  // uint64_t

#include <string>
#include <vector>
#include <map>
#include <utility>  // std::pair, std::make_pair

#include "ml.hh"

namespace argcv {
namespace ml {

class sgd : public ml<double, double> {
public:
    sgd() {
        printf("sgd() starting ..\n");
    }

    sgd(dataset<double, double> data) : data(data) {
        printf("sgd(dataset_dd) starting ..\n");
    }

    ~sgd() {
        printf("sgd finished ..\n");
    }

    void add(std::vector<double> x, double y) { data.add(x, y); }
    

    bool learn() { return false; }

    bool save(const std::string &path) { return false; }

    bool load(const std::string &path) { return false; }

    double predict(std::vector<double> x) {
        return 0;
    }

private:
    dataset<double, double> data;
};
}
}  // namespace argcv::ml

#endif  //  ARGCV_ML_SGD_HH
