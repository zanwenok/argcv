/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Yu Jing <yu@argcv.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/
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
