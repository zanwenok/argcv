#ifndef ARGCV_STORAGE_HD_STORAGE_HH
#define ARGCV_STORAGE_HD_STORAGE_HH

#include <map>
#include <set>
#include <string>
#include <vector>

#include "argcv/storage/storage.hh"

#include "argcv/wrapper/leveldb_wr.hh"

namespace argcv {
namespace storage {

class hd_storage : public storage {
public:
    hd_storage(const std::string& config);

    virtual ~hd_storage();

    bool conn();
    bool close();
    bool is_closed();

    bool start_with(const std::string& base,
                    bool (*kv_handler)(const std::string&, const std::string&, void*), void* data = nullptr,
                    const std::string& selector = "");
    bool exist(const std::string& key, const std::string& selector = "");
    bool put(const std::string& key, const std::string& val = "", const std::string& selector = "");
    bool get(const std::string& key, std::string* _val, const std::string& selector = "");
    bool rm(const std::string& key, const std::string& selector = "");

    bool batch_put(const std::map<std::string, std::pair<std::string,std::string>>& kvs);
    bool batch_rm(const std::set<std::pair<std::string,std::string>>& keys);

    const size_t _cache_size() const;
    const bool _create_if_missing() const;

    const int _err_no() { return err_no; }

private:
    const std::string config;
    std::string db_prefix;
    size_t sz_shard;
    size_t sz_cache;
    int err_no;
    ::argcv::wrapper::leveldb::ldb_wr* _db;
};
}
}  //  namespace argcv::storage

#endif  //  ARGCV_STORAGE_HD_STORAGE_HH