/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Yu Jing <yu@argcv.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/
#ifndef ARGCV_ML_SVM_HH
#define ARGCV_ML_SVM_HH

// Support Vector Machine
//
// Progress:
// NOT STARTED
// ref: http://blog.pluskid.org/?p=632

#include <cstdint>  // uint64_t
#include <cstdio>

#include <map>
#include <string>
#include <utility>  // std::pair, std::make_pair
#include <vector>

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

    bool predict(std::vector<double> x) { return false; }

private:
    dataset<double, bool> data;
};
}
}  // namespace argcv::ml

#endif  //  ARGCV_ML_SVM_HH
