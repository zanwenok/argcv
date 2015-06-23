#ifndef ARGCV_STRING_STRING_HH
#define ARGCV_STRING_STRING_HH

#include <cstring>

#include <vector>
#include <string>
#include <algorithm>

namespace argcv {
namespace string {

inline std::vector<std::string> &split(const std::string &s, const std::string &delim,
                                       std::vector<std::string> *_elems) {
    std::string item;
    if (delim.empty()) {
        _elems->push_back(s);
        return *_elems;
    }
    std::string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        std::string temp(substart, subend);
        // if (keep_empty || !temp.empty()) {
        if (!temp.empty()) {
            _elems->push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return *_elems;
}

inline std::vector<std::string> split(const std::string &s, const std::string &delim) {
    std::vector<std::string> elems;
    split(s, delim, &elems);
    return elems;
}

inline std::string replace(std::string &str_raw, const std::string &str_src, const std::string &str_dst) {
    std::string::size_type pos = 0;
    std::string::size_type src_len = str_src.size();
    std::string::size_type dst_len = str_dst.size();
    while ((pos = str_raw.find(str_src, pos)) != std::string::npos) {
        str_raw.replace(pos, src_len, str_dst);
        pos += dst_len;
    }
    return str_raw;
}

template <typename T>
std::string as_str(T v) {
    return std::string((char *)&v, sizeof(T));
}

template <typename T>
std::string as_str(std::vector<T> v) {
    std::string r;
    for (size_t ix = 0; ix < v.size(); ix++) {
        r += std::string((char *)(&(v[ix])), sizeof(T));
    }
    return r;
}

template <typename T>
T as_type(const std::string s) {
    T v;
    size_t sz = sizeof(T);
    if (s.size() < sz) {
        memset(&v, 0, sz);
    } else {
        memcpy(&v, s.data(), sz);
    }
    return v;
}

template <typename T>
T as_type(const std::string s, size_t offset) {
    T v;
    size_t sz = sizeof(T);
    if (s.size() < sz + offset) {
        memset(&v, 0, sz);
    } else {
        memcpy(&v, s.data() + offset, sz);
    }
    return v;
}

template <typename T>
std::vector<T> as_vec(const std::string s, size_t offset = 0) {
    std::vector<T> v;
    size_t tsz = sizeof(T);
    size_t sz = (s.size() - offset) / tsz;
    for (size_t ix = 0; ix < sz; ix++) {
        T tv;
        memcpy(&tv, ((char *)s.data()) + ix * tsz + offset, tsz);
        v.push_back(tv);
    }
    return v;
}
/*
const char* ddir = "leveldb.data";
ldb_wrapper lw(ddir, 0, true);
lw.conn();

argcv::ir::index::analyzer::basic_tokenlizer tokens("abc def ghi");
argcv::ir::index::analyzer::basic_analyzer anas(&tokens);
std::string t;
std::string pr;
std::string cu;
anas.prev(pr);
while (anas.next(t)) {
    anas.curr(cu);
    printf("t:[%s]#%s#%s\n", pr.c_str(), cu.c_str(), t.c_str());
    anas.prev(pr);
}
anas.reset();
anas.prev(pr);
printf("restart ... \n");
while (anas.next(t)) {
    anas.curr(cu);
    printf("t:[%s]#%s#%s\n", pr.c_str(), cu.c_str(), t.c_str());
    anas.prev(pr);
}

int v = 1024;
char* xv = (char*)&v;
std::string v_as_str = as_str<int>(v);
char* s_xv = (char*)v_as_str.data();
printf("size : %lu , %lu \n", v_as_str.size(), sizeof(v));
for (int i = 0; i < sizeof(v); i++) {
    printf("c: %u - %u  - %u\n", (unsigned)(v_as_str[i]), (unsigned)(xv[i]), (unsigned)(s_xv[i]));
}
int v_as_str_as_u = as_type<int>(v_as_str);

printf("%d\n", v_as_str_as_u);

std::vector<int> info;
info.push_back(1);
info.push_back(2);
info.push_back(3);
info.push_back(4);
std::string info_as_str = as_str<int>(info);

lw.put(v_as_str, info_as_str);

std::vector<int> info2 = as_vec<int>(lw[v_as_str]);

for (size_t ix = 0; ix < info2.size(); ix++) {
    printf("## %d \n", info2[ix]);
}

lw.close();
*/

inline int utf8_char_length(unsigned char ch) {
    unsigned char t = 0x80;
    if (!(ch & t))  // ! 1000 0000 B
        return 1;
    t = t >> 1;
    if (!(ch & t))  // ! 0100 0000 B
        return 0;
    t = t >> 1;
    int l = 2;
    while (ch & t) {
        t = t >> 1;
        l++;
        if (l > 6) return 0;
    }
    return l;
}

inline std::vector<std::string> utf8split(const std::string &s) {
    std::vector<std::string> elems;
    size_t clen = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if ((clen = utf8_char_length(s[i]))) {
            elems.push_back(s.substr(i, clen));
            i += clen - 1;
        } else {
            // fprintf(stderr, "error size: %zu %zu\n", clen, i);
            break;
        }
    }
    return elems;
}
}
}  // argcv::string

#endif  //  ARGCV_STRING_STRING_HH
