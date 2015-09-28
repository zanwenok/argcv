#ifndef ARGCV_STORAGE_STORAGE_HH
#define ARGCV_STORAGE_STORAGE_HH
#include <map>
#include <set>
#include <string>
#include <vector>

namespace argcv {
namespace storage {

class storage {
public:
    class stg_bw_handler {
    public:
        virtual ~stg_bw_handler() {}
        virtual void put(const std::string& key, const std::string& val = "",
                         const std::string& selector = "")
            = 0;
        virtual void rm(const std::string& key, const std::string& selector = "") = 0;
        virtual bool commit() = 0;
        virtual bool _err() = 0;
    };

public:
    virtual bool conn() = 0;
    virtual bool close() = 0;
    virtual bool is_closed() = 0;

    virtual bool start_with(const std::string& base,
                            bool (*kv_handler)(const std::string&, const std::string&, void*),
                            void* data = nullptr, const std::string& selector = "")
        = 0;

    virtual bool exist(const std::string& key, const std::string& selector = "") = 0;
    virtual bool put(const std::string& key, const std::string& val = "", const std::string& selector = "")
        = 0;
    virtual bool get(const std::string& key, std::string* _val, const std::string& selector = "") = 0;
    virtual bool rm(const std::string& key, const std::string& selector = "") = 0;

    virtual stg_bw_handler* batch_writer() = 0;

    virtual bool batch_put(const std::map<std::string, std::pair<std::string, std::string>>& kvs) = 0;
    virtual bool batch_rm(const std::set<std::pair<std::string, std::string>>& keys) = 0;
};

typedef storage::stg_bw_handler stg_bw_handler;
}
}  //  namespace argcv::storage

#endif  //  ARGCV_STORAGE_STORAGE_HH