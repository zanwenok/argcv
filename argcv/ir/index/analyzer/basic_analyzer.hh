#ifndef ARGCV_IR_INDEX_ANALYZER_BASIC_ANALYZER_HH
#define ARGCV_IR_INDEX_ANALYZER_BASIC_ANALYZER_HH

#include "analyzer.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class basic_analyzer : public analyzer {
public:
    basic_analyzer(tokenlizer* _t) : analyzer(_t) {}
    bool prev(std::string& t) { return _t->prev(t); }
    bool curr(std::string& t) { return _t->curr(t); }
    bool next(std::string& t) { return _t->next(t); }
    bool reset() { return _t->reset(); }
    bool end() { return _t->end(); }
    bool begin() { return _t->begin(); }
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_BASIC_ANALYZER_HH
