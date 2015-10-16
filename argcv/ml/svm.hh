#ifndef ARGCV_ML_SVM_HH
#define ARGCV_ML_SVM_HH

// Perceptron
// In machine learning, the perceptron is an algorithm for supervised
// classification of an input into one of several possible non-binary outputs.

// Progress:
// NOT STARTED

#include <cstdio>
#include <cstdint>  // uint64_t

#include <string>
#include <vector>
#include <map>
#include <utility>  // std::pair, std::make_pair

#include "ml.hh"

namespace argcv {
namespace ml {

class svm : public ml<double, bool> {
public:
    svm() {}

    svm(dataset<double, bool> data) : data(data) {}

    ~svm() {}

    void add(std::vector<double> x, bool y) { data.add(x, y); }
    

    bool learn() { return false; }

    bool save(const std::string &path) { return false; }

    bool load(const std::string &path) { return false; }

    bool predict(std::vector<double> x) {
        return false;
    }

private:
    dataset<double, bool> data;
};
}
}  // namespace argcv::ml

#endif  //  ARGCV_ML_SVM_HH
