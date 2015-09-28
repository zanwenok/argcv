#ifndef ARGCV_IR_INDEX_ANALYZER_BASIC_TOKENLIZER_HH
#define ARGCV_IR_INDEX_ANALYZER_BASIC_TOKENLIZER_HH

#include <string>
#include <vector>
#include "tokenlizer.hh"

#include "argcv/string/string.hh"
#include "argcv/string/chars.h"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class basic_tokenlizer : public tokenlizer {
public:
    basic_tokenlizer(const std::string& s)
        : tokenlizer(s), data(argcv::string::stemm_s(s)), offset(0), size(data.size()) {}

    bool prev(std::string& t) { return begin() ? false : (t.assign(data[offset - 1]), true); }
    bool next(std::string& t) { return end() ? false : (t.assign(data[offset]), offset++, true); }
    bool curr(std::string& t) { return end() ? false : (t.assign(data[offset]), true); }
    bool reset() { return (offset = 0, true); }
    bool end() { return offset >= size; }
    bool begin() { return offset == 0; }

protected:
    std::vector<std::string> data;
    size_t offset;
    size_t size;
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_BASIC_TOKENLIZER_HH
