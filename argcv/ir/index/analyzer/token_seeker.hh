#ifndef ARGCV_IR_INDEX_ANALYZER_TOKEN_SEEKER_HH
#define ARGCV_IR_INDEX_ANALYZER_TOKEN_SEEKER_HH

#include <string>

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class token_seeker {
public:
    virtual bool prev(std::string& t) = 0;
    virtual bool curr(std::string& t) = 0;
    virtual bool next(std::string& t) = 0;
    virtual bool reset() = 0;
    virtual bool end() = 0;
    virtual bool begin() = 0;
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_TOKEN_SEEKER_HH
