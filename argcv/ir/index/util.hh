#ifndef ARGCV_IR_INDEX_UTIL_HH
#define ARGCV_IR_INDEX_UTIL_HH

#include <string>

namespace argcv {
namespace ir {
namespace index {

const static std::string DB_SEPARATOR("\0", 1);
//const static std::string DB_SEPARATOR("#", 1);

inline std::string index_db_doc_prefix() {
    std::string _prefix("D");  // shall I use 'static std::string' ?
    return _prefix;
}

inline std::string index_db_idx_prefix() {
    std::string _prefix("I");
    return _prefix;
}

const static std::string DB_DOC_PREFIX(index_db_doc_prefix());
const static std::string DB_IDX_PREFIX(index_db_idx_prefix());

inline std::string index_db_meta_prefix() {
    std::string _prefix("M");
    return _prefix;
}

const static std::string DB_META_PREFIX(index_db_meta_prefix());

}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_UTIL_HH