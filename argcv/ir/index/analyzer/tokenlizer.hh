#ifndef ARGCV_IR_INDEX_ANALYZER_TOKENLIZER_HH
#define ARGCV_IR_INDEX_ANALYZER_TOKENLIZER_HH

#include <string>

#include "token_seeker.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class tokenlizer : public token_seeker {
public:
    tokenlizer(const std::string& s) : token_seeker(), s(s) {}

protected:
    const std::string s;
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_TOKENLIZER_HH
