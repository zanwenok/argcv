#ifndef ARGCV_IR_INDEX_INDEX_HH
#define ARGCV_IR_INDEX_INDEX_HH

#include "analyzer/analyzer.hh"
#include <string>

namespace argcv {
namespace ir {
namespace index {
class index {
public:
    index(const std::string& path, size_t cache_size = 0, size_t shard = 5)
        : path(path), cache_size(cache_size), shard(shard) {}
    virtual ~index();

private:
    const std::string path;
    size_t cache_size;
    size_t shard;
};
}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_INDEX_HH
