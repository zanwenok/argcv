#ifndef ARGCV_IR_INDEX_ANALYZER_LEXICON_HH
#define ARGCV_IR_INDEX_ANALYZER_LEXICON_HH

#include <string>

#include "argcv/string/string.hh"
#include "argcv/wrapper/leveldb_wr.hh"

namespace argcv {
namespace ir {
namespace index {
namespace analyzer {
using ::argcv::wrapper::leveldb::ldb_wr;
using ::argcv::string::as_type;
using ::argcv::string::as_str;

class lexicon {
public:
    lexicon(const std::string& dpath, size_t cache_size = 0) : db(ldb_wr(dpath, cache_size)) { db.conn(); }
    ~lexicon() { db.close(); }

    void set(const std::string& term, size_t sz = 0) { db.put(term, as_str<size_t>(sz)); }
    void unset(const std::string& term) { db.rm(term); }
    size_t count(const std::string& term) {
        std::string rt;
        db.get(term, &rt);
        return as_type<size_t>(rt);
    }

    size_t level(const std::string& term) {
        size_t c = count(term);
        size_t lv = 0;
        while (c > 0) {
            lv++;
            c = c >> 4;
        }
        return lv;
    }

private:
    ldb_wr db;
};
}
}
}
}  // namespace argcv::ir::index::analyzer

#endif  //  ARGCV_IR_INDEX_ANALYZER_LEXICON_HH
