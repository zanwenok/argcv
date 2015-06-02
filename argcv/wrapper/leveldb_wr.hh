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

struct ldb_info;

class ldb_wrapper {
public:
    ldb_wrapper(const std::string& ddir, size_t cache_size = 0, bool create_if_missing = true)
        : ddir(ddir), cache_size(cache_size), create_if_missing(create_if_missing) {
        _info = nullptr;
    }

    bool conn();
    bool close();
    bool is_closed() { return _info == nullptr; }

    // WARNING : WILL ERASE ALL DATA IN THIS DIR
    // SHALL CLOSE THE DB BEFORE CALL THIS FUNCTION
    static bool destroy(const std::string& ddir);

    virtual ~ldb_wrapper();

    bool start_with(const std::string& base,
                    bool (*kv_handler)(const std::string&, const std::string&, void*), void* data = nullptr);
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
    ldb_info* _info;

    class ldb_wrapper_agent {
    public:
        ldb_wrapper_agent(ldb_wrapper& m_o, const std::string& m_k) : o(m_o), k(m_k) {}

        // get value of key
        operator std::string() const {
            std::string v;
            o.get(k, &v);
            return v;
        }

        // exist this value 
        operator bool() const { return o.exist(k); }

        void operator=(const std::string& v) { o.put(k, v); }

    private:
        ldb_wrapper& o;
        const std::string k;
    };

public:
    ldb_wrapper_agent operator[](const std::string& k) { return ldb_wrapper_agent(*this, k); }
};

/*

*/
}
}
}  // namespace argcv::wrapper::leveldb

#endif  // ARGCV_WRAPPER_LEVELDB_WR_HH
