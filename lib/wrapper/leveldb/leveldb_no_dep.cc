#include "argcv/wrapper/leveldb_wr.hh"

namespace argcv {
namespace wrapper {
namespace leveldb {

typedef bool (*kv_handler)(const std::string&, const std::string&, void*);

typedef struct ldb_info {
} ldb_info;

bool ldb_wr::conn() { return false; }

bool ldb_wr::close() { return true; }

bool ldb_wr::destroy(const std::string& ddir) { return true; }

ldb_wr::~ldb_wr() {}

bool ldb_wr::start_with(const std::string& base, kv_handler kvs, void* data) { return false; }
bool ldb_wr::exist(const std::string& key) { return false; }
bool ldb_wr::put(const std::string& key, const std::string& val) { return false; }
bool ldb_wr::get(const std::string& key, std::string* _val) { return false; }
bool ldb_wr::rm(const std::string& key) { return false; }

bool ldb_wr::batch_put(const std::map<std::string, std::string>& kvs) { return false; }
bool ldb_wr::batch_rm(const std::set<std::string>& keys) { return false; }
}
}
}