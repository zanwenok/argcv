#ifndef ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH
#define ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH

#include <string>
#include <vector>

#include "token_seeker.hh"
#include "tokenlizer.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class analyzer : public token_seeker {
public:
    analyzer(tokenlizer* _t) : token_seeker(), _t(_t) {}

    std::vector<std::string> to_vec() {
        std::vector<std::string> _v;
        std::string s;
        reset();
        while (next(s)) _v.push_back(s);
        return _v;
    }

protected:
    tokenlizer* _t;
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH
