#ifndef ARGCV_WRAPPER_INI_WR_HH
#define ARGCV_WRAPPER_INI_WR_HH

#include <cstdlib>

#include <map>
#include <string>

//#include "leveldb/db.h"
//#include "leveldb/cache.h"
//#include "leveldb/options.h"

namespace argcv {
namespace wrapper {
namespace ini {

class ini_wr {
private:
    class sec {
    private:
        class sec_val {
        public:
            sec_val(ini_wr &iw, const std::string &sn, const std::string &k) : iw(iw), sn(sn), k(k) {}

            // set & get const std::string &

            operator const std::string &() const {
                // printf("get<const std::string &> [%s][%s]\n", sn.c_str(), k.c_str());
                return get();
            }

            void operator=(const std::string &v) {
                // printf("set: [%s][%s] => [%s]\n", sn.c_str(), k.c_str(), v.c_str());
                set(v);
            }

            const std::string &get() const {
                if (exist()) {
                    return iw.d[sn][k];
                } else {
                    return iw.nil_val;
                }
            }

            void set(const std::string &v) {
                if (iw.d.find(sn) == iw.d.end()) {
                    iw.d[sn] = std::map<std::string, std::string>();
                }
                iw.d[sn][k] = v;
            }

            // set & get int
            operator const int() const {
                // printf("get int [%s][%s]\n", sn.c_str(), k.c_str());
                return get_int();
            }

            void operator=(int v) {
                // printf("set int : [%s][%s] => [%d]\n", sn.c_str(), k.c_str(), v);
                set_int(v);
            }

            int get_int() const { return atoi(get().c_str()); }

            void set_int(int v) { set(std::to_string(v)); }

            // set & get double
            operator const double() const {
                // printf("get double [%s][%s]\n", sn.c_str(), k.c_str());
                return get_double();
            }

            void operator=(double v) {
                // printf("set double : [%s][%s] => [%f]\n", sn.c_str(), k.c_str(), v);
                set_double(v);
            }

            int get_double() const { return atof(get().c_str()); }

            void set_double(double v) { set(std::to_string(v)); }

            bool exist() const { return iw.d.find(sn) != iw.d.end() && iw.d[sn].find(k) != iw.d[sn].end(); }

        private:
            ini_wr &iw;
            const std::string &sn;
            const std::string &k;
        };

    public:
        sec(ini_wr &iw, const std::string &sn) : iw(iw), sn(sn) {}
        sec_val operator[](const std::string &k) { return sec_val(iw, sn, k); }

    private:
        ini_wr &iw;
        const std::string &sn;
    };

public:
    ini_wr(const std::string &path, const std::string &nil_val = "");
    sec operator[](const std::string &k) { return sec(*this, k); }

private:
    const std::string path;
    const std::string nil_val;
    std::map<std::string, std::map<std::string, std::string>> d;
};
}
}
}  // namespace argcv::wrapper::ini

#endif  // ARGCV_WRAPPER_INI_WR_HH
