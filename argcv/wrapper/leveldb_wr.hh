#ifndef ARGCV_WRAPPER_LEVELDB_WR_HH
#define ARGCV_WRAPPER_LEVELDB_WR_HH

#include <map>
#include <set>
#include <string>

//#include "leveldb/db.h"
//#include "leveldb/cache.h"
//#include "leveldb/options.h"

namespace argcv {
namespace wrapper {
namespace leveldb {

typedef bool (*key_val_cb)(const std::string&, const std::string&);

struct ldb_info;

class ldb_wrapper {
public:
    ldb_wrapper(const std::string& ddir, size_t cache_size = 0, bool create_if_missing = true)
        : ddir(ddir), cache_size(cache_size), create_if_missing(create_if_missing) {
        init();
    }

    virtual ~ldb_wrapper();

    bool start_with(const std::string& base, key_val_cb kvs);
    bool exist(const std::string& key);
    bool put(const std::string& key, const std::string& val = "");
    bool get(const std::string& key, std::string* _val);
    bool rm(const std::string& key);

    bool batch_put(const std::map<std::string, std::string>& kvs);
    bool batch_rm(const std::set<std::string>& keys);

private:
    const std::string ddir;
    size_t cache_size;
    bool create_if_missing;
    ldb_info * _info;

    bool init();
};
}
}
}  // namespace argcv::wrapper::leveldb

#endif  // ARGCV_WRAPPER_LEVELDB_WR_HH
