#ifndef ARGCV_ML_LOGISTIC_REGRESSION_HH
#define ARGCV_ML_LOGISTIC_REGRESSION_HH

// logistic regression

// f(z) = 1 / ( 1 + pow(M_E,-z))

//
// Progress:
// NOT STARTED
#include <cmath>  // pow
#include <cstdio>
#include <cstdint>  // uint64_t

#include <string>
#include <vector>
#include <map>
#include <utility>  // std::pair, std::make_pair

#include "ml.hh"

namespace argcv {
namespace ml {

class logistic_regression : public ml<double, double> {
public:
    logistic_regression() {}

    logistic_regression(dataset<double, double> data) : data(data) {}

    ~logistic_regression() {}

    void add(std::vector<double> x, double y) { data.add(x, y); }

    bool learn() { return false; }

    bool save(const std::string &path) { return false; }

    bool load(const std::string &path) { return false; }

    double predict(std::vector<double> x) { return 0.0; }

private:
    dataset<double, double> data;
};
}
}  // namespace argcv::ml

#endif  //  ARGCV_ML_LOGISTIC_REGRESSION_HH
