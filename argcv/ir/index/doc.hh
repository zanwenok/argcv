#ifndef ARGCV_IR_INDEX_DOC_HH
#define ARGCV_IR_INDEX_DOC_HH

#include <string>

#include "field.hh"
#include "util.hh"
#include "argcv/storage/storage.hh"

namespace argcv {
namespace ir {
namespace index {

using ::argcv::storage::storage;

class doc {
public:
    doc(const std::string& id, storage* _stg) : id(id), _stg(_stg) { printf("doc:start\n"); }
    virtual ~doc() { printf("doc:end\n"); }

    const std::string& _id() { return id; }

    std::string get(const std::string& field) const { return get_str(field); }

    std::string get_str(const std::string& field) const {
        std::string k = DB_DOC_PREFIX;
        k += id;
        k += DB_SEPARATOR;
        k += field;
        std::string val;
        _stg->get(k, &val);
        return val;
    }

private:
    const std::string id;
    storage* _stg;
};
}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_DOC_HH