#ifndef ARGCV_IR_INDEX_INDEX_HH
#define ARGCV_IR_INDEX_INDEX_HH

#include <string>

#include "doc.hh"
#include "util.hh"
#include "analyzer/analyzer.hh"
#include "argcv/storage/storage.hh"
#include "argcv/wrapper/leveldb_wr.hh"

namespace argcv {
namespace ir {
namespace index {

using ::argcv::wrapper::leveldb::ldb_wr;
using ::argcv::storage::storage;

class index {
public:
    index(storage* _stg);
    virtual ~index();

    bool db_status() { return !_stg->is_closed(); }
    doc get(const std::string& id) { return doc(id, _stg); }

private:
    storage* _stg;
};
}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_INDEX_HH
