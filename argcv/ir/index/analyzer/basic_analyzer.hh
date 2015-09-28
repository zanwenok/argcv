#ifndef ARGCV_IR_INDEX_ANALYZER_BASIC_ANALYZER_HH
#define ARGCV_IR_INDEX_ANALYZER_BASIC_ANALYZER_HH

#include "analyzer.hh"

#include "argcv/string/chars.h"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
class basic_analyzer : public analyzer {
public:
    basic_analyzer(tokenlizer* _t) : analyzer(_t) {
        _t->reset();
        std::string s;
        while (_t->next(s)) {
            if (s.length() > 0 && !is_western_punct(s[0])) {
                // printf("%s %d add: %s\n", __FILE__, __LINE__, s.c_str());
                data.push_back(s);
            } else {
                // printf("%s %d ignore: %s\n", __FILE__, __LINE__, s.c_str());
            }
        }
        offset = 0;
        size = data.size();
    }

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

#endif  //  ARGCV_IR_INDEX_ANALYZER_BASIC_ANALYZER_HH
