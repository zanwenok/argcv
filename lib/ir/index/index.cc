#include "argcv/ir/index/index.hh"

#include <cstdio>

#include <map>
#include <set>
#include <string>

#include "argcv/ir/index/analyzer/analyzer.hh"
#include "argcv/storage/storage.hh"
#include "argcv/wrapper/leveldb_wr.hh"

namespace argcv {
namespace ir {
namespace index {
using ::argcv::wrapper::leveldb::ldb_wr;
using ::argcv::storage::storage;

index::index(storage* _stg) : _stg(_stg) {
    printf("index started\n");
    _stg->conn();
}

index::~index() {
    _stg->close();
    printf("index destroied\n");
}


}
}
}  // namespace argcv::ir::index