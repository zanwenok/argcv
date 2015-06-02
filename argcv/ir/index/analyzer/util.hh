#ifndef ARGCV_IR_INDEX_ANALYZER_UTIL_HH
#define ARGCV_IR_INDEX_ANALYZER_UTIL_HH

#include <map>

#include "analyzer.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {

inline std::map<std::string, uint64_t> token_stat(analyzer* _t) {
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
