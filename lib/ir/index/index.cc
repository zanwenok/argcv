#include "argcv/ir/index/index.hh"

#include <cstdio>

namespace argcv {
namespace ir {
namespace index {

index::index(const std::string& path, size_t cache_size, size_t shard)
    : path(path), cache_size(cache_size), shard(shard) {
    printf("index started %s , %zu , %zu\n", path.c_str(), cache_size, shard);
}

index::~index() { printf("index destroied %s , %zu , %zu\n", path.c_str(), cache_size, shard); }
}
}
}