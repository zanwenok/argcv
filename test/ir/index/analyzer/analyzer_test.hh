#ifndef ARGCV_TEST_IR_INDEX_ANALYZER_ANALYZER_TEST_HH
#define ARGCV_TEST_IR_INDEX_ANALYZER_ANALYZER_TEST_HH
#include "test/argcv_test.h"

#include <map>
#include <string>

#include "argcv/ir/ir.hh"
#include "argcv/ir/index/index.hh"
#include "argcv/ir/index/analyzer/basic_analyzer.hh"
#include "argcv/ir/index/analyzer/basic_tokenlizer.hh"
#include "argcv/ir/index/analyzer/util.hh"

using namespace argcv::string;
using namespace argcv::ir::index::analyzer;

static int test_case_analyzer_basic(int argc, char* argv[]) {
    std::string s(
        "Searches the container for an element with a key equivalent to k and returns an iterator to it if "
        "found, otherwise it returns an iterator to map::end.Two keys are considered equivalent if the "
        "container\'s comparison object returns false reflexively (i.e., no matter the order in which the "
        "elements are passed as arguments).Another member function, map::count, can be used to just check "
        "whether a particular key exists.");
    basic_tokenlizer t(s);
    basic_analyzer a(&t);
    std::map<std::string, uint64_t> stats(token_stat(&a));

    for (std::map<std::string, uint64_t>::const_iterator it = stats.begin(); it != stats.end(); it++) {
        printf("key: %s value: %llu\n", it->first.c_str(), it->second);
    }
    return 0;
}

#endif  // ARGCV_TEST_IR_INDEX_ANALYZER_ANALYZER_TEST_HH