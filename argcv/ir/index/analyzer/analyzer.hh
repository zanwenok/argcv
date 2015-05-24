#ifndef ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH
#define ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH

#include "token_seeker.hh"
#include "tokenlizer.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class analyzer : public token_seeker {
public:
    analyzer(tokenlizer* _t) : token_seeker(), _t(_t) {}

protected:
    tokenlizer* _t;
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_ANALYZER_HH
