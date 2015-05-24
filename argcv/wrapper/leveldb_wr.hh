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
bool key_value_printer(const std::string& k, const std::string& v, void* data) {
    int* _offset = (int*)data;
    printf("%d key: %s \t value: %s \n", (*_offset)++, k.c_str(), v.c_str());
    return true;  //(*_offset) < 2;
}

void use_ldb(){
const char* ddir = "leveldb.data";
ldb_wrapper lw(ddir, 0, true);
lw.conn();
lw.put("a", "00");
lw.put("a01", "01");
lw.put("a02", "02");
// lw.put("a03", "03");
printf("destroy status : %d \n", ldb_wrapper::destroy(ddir));
lw.put("a04", "04");
lw.put("b01", "04");
lw.put("b03", "05");
printf("exist a? %d \n", lw.exist("a") ? 1 : 0);

map<string, string> kvs_to_put;
kvs_to_put["a07"] = "x07";
kvs_to_put["a08"] = "x08";
kvs_to_put["a09"] = "x09";
kvs_to_put["a10"] = "";

set<string> keys_to_del;
keys_to_del.insert("a04");

lw.batch_put(kvs_to_put);
lw.batch_rm(keys_to_del);

lw.rm("a02");
int i = 0;

lw["a80"] = "80";

printf("single get : a80: %s \n", static_cast<std::string>(lw["a80"]).c_str());
printf("single get : a81: %s \n", static_cast<std::string>(lw["a81"]).c_str());
printf("single exist : a81: %d \n", static_cast<bool>(lw["a81"]));

lw.start_with("a", key_value_printer, &i);

printf("destroy status : %d \n", ldb_wrapper::destroy(ddir));

printf("is closed ? %d \n", lw.is_closed() ? 1 : 0);
lw.close();
}
*/
}
}
}  // namespace argcv::wrapper::leveldb

#endif  // ARGCV_WRAPPER_LEVELDB_WR_HH
