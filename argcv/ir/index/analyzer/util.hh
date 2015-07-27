#ifndef ARGCV_IR_INDEX_ANALYZER_UTIL_HH
#define ARGCV_IR_INDEX_ANALYZER_UTIL_HH

#include <map>
#include <string>   // std::string
#include <vector>   // vector
#include <utility>  // make_pair

#include "analyzer.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {

inline std::map<std::string, std::pair<uint64_t, std::vector<uint32_t>>> token_stat(analyzer* _t) {
    std::map<std::string, std::pair<uint64_t, std::vector<uint32_t>>> s;
    std::string v;
    _t->reset();
    size_t pos = 0;
    while (_t->next(v)) {
        if (s.find(v) == s.end()) {
            std::vector<uint32_t> pl;
            pl.push_back(pos);
            s[v] = std::make_pair(1,pl);
        } else {
            s[v].first ++;
            s[v].second.push_back(pos);
        }
        pos++;
    }
    return s;
}

inline std::map<std::string, uint64_t> token_stat_c(analyzer* _t) {
    std::map<std::string, uint64_t> s;
    std::string v;
    _t->reset();
    while (_t->next(v)) {
        if (s.find(v) == s.end()) {
            s[v] = 1;
        } else {
            s[v]++;
        }
    }
    return s;
}
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_UTIL_HH
