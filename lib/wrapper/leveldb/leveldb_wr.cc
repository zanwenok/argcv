#include "argcv/wrapper/leveldb_wr.hh"

#include <map>
#include <set>

#include "leveldb/db.h"
#include "leveldb/cache.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"

namespace argcv {
namespace wrapper {
namespace leveldb {

// low level apis
::leveldb::DB* ldb_init(const std::string& ddir, ::leveldb::Options* _opt, size_t cache_size = 0,
                        bool create_if_missing = true);
bool ldb_close(::leveldb::DB* db, ::leveldb::Options* _opt);

bool ldb_start_with(::leveldb::DB* db, const std::string& base, key_val_cb kvs);
bool ldb_exist(::leveldb::DB* db, const std::string& key);
bool ldb_put(::leveldb::DB* db, const std::string& key, const std::string& val = "");
bool ldb_get(::leveldb::DB* db, const std::string& key, std::string* _val);
bool ldb_rm(::leveldb::DB* db, const std::string& key);

bool ldb_batch_put(::leveldb::DB* db, const std::map<std::string, std::string>& kvs);
bool ldb_batch_rm(::leveldb::DB* db, const std::set<std::string>& keys);

typedef struct ldb_info {
    ::leveldb::DB* db;
    ::leveldb::Options opt;
} ldb_info;

bool ldb_wrapper::init() {
    _info = new ldb_info;
    _info->db = ldb_init(ddir, &(_info->opt), cache_size, create_if_missing);
    return _info->db != nullptr;
}

ldb_wrapper::~ldb_wrapper() {
    if (_info != nullptr) {
        ldb_close(_info->db, &(_info->opt));
        delete _info;
    }
}

bool ldb_wrapper::start_with(const std::string& base, key_val_cb kvs) {
    return ldb_start_with(_info->db, base, kvs);
}
bool ldb_wrapper::exist(const std::string& key) { return ldb_exist(_info->db, key); }
bool ldb_wrapper::put(const std::string& key, const std::string& val) { return ldb_put(_info->db, key, val); }
bool ldb_wrapper::get(const std::string& key, std::string* _val) { return ldb_get(_info->db, key, _val); }
bool ldb_wrapper::rm(const std::string& key) { return ldb_rm(_info->db, key); }

bool ldb_wrapper::batch_put(const std::map<std::string, std::string>& kvs) { return ldb_batch_put(_info->db, kvs); }
bool ldb_wrapper::batch_rm(const std::set<std::string>& keys) { return ldb_batch_rm(_info->db, keys); }

::leveldb::DB* ldb_init(const std::string& ddir, ::leveldb::Options* _opt, size_t cache_size,
                        bool create_if_missing) {
    if (_opt == nullptr) {
        return nullptr;
    }
    _opt->create_if_missing = create_if_missing;
    if (cache_size > 0) {
        _opt->block_cache = ::leveldb::NewLRUCache(cache_size);
    }

    ::leveldb::DB* db;
    return ::leveldb::DB::Open(*_opt, ddir, &db).ok() ? db : nullptr;
}

bool ldb_close(::leveldb::DB* db, ::leveldb::Options* _opt) {
    if (_opt != nullptr && _opt->block_cache != nullptr) {
        delete _opt->block_cache;
    }
    if (db == nullptr) {
        return false;
    }
    delete db;
    return true;
}

bool ldb_start_with(::leveldb::DB* db, const std::string& base, key_val_cb kvs) {
    ::leveldb::ReadOptions snap_read_opt;
    snap_read_opt.snapshot = db->GetSnapshot();
    ::leveldb::Iterator* it = db->NewIterator(snap_read_opt);
    ::leveldb::Slice slice = base;
    for (it->Seek(slice);
         it->Valid()
         && std::mismatch(base.begin(), base.end(), it->key().ToString().begin()).first == base.end();
         it->Next()) {
        if (!kvs(it->key().ToString(), it->value().ToString())) {
            break;
        }
    }
    delete it;
    db->ReleaseSnapshot(snap_read_opt.snapshot);
    return true;
}

bool ldb_exist(::leveldb::DB* db, const std::string& key) {
    std::string val;
    return ((db->Get(::leveldb::ReadOptions(), key, &val)).ok());
}

bool ldb_put(::leveldb::DB* db, const std::string& key, const std::string& val) {
    return ((db->Put(::leveldb::WriteOptions(), key, val)).ok());
}

bool ldb_get(::leveldb::DB* db, const std::string& key, std::string* _val) {
    return ((db->Get(::leveldb::ReadOptions(), key, _val)).ok());
}

bool ldb_rm(::leveldb::DB* db, const std::string& key) {
    return ((db->Delete(::leveldb::WriteOptions(), key)).ok());
}

bool ldb_batch_put(::leveldb::DB* db, const std::map<std::string, std::string>& kvs) {
    ::leveldb::WriteBatch* _wb = new ::leveldb::WriteBatch;
    for (std::map<std::string, std::string>::const_iterator it = kvs.begin(); it != kvs.end(); it++) {
        // printf("ldb_batch_add %s -> %s\n", it->first.c_str(), it->second.c_str());
        _wb->Put(it->first, it->second);
    }
    bool rst = ((db->Write(::leveldb::WriteOptions(), _wb)).ok());
    delete _wb;
    return rst;
}

bool ldb_batch_rm(::leveldb::DB* db, const std::set<std::string>& keys) {
    ::leveldb::WriteBatch* _wb = new ::leveldb::WriteBatch;
    for (std::set<std::string, std::string>::const_iterator it = keys.begin(); it != keys.end(); it++) {
        _wb->Delete(*it);
    }
    bool rst = ((db->Write(::leveldb::WriteOptions(), _wb)).ok());
    delete _wb;
    return rst;
}
}
}
}