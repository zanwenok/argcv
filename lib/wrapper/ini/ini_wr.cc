#include "argcv/wrapper/ini_wr.hh"

#include <cstdio>

#include <string>

#include "ini.h"

namespace argcv {
namespace wrapper {
namespace ini {

int ini_handler(void* user, const char* section, const char* name, const char* value) {
    (*(ini_wr*)user)[section][name] = value;
    return 0;
}

ini_wr::ini_wr(const std::string& path, const std::string& nil_val) : path(path), nil_val(nil_val) {
    ini_parse(path.c_str(), ini_handler, this);
}
}
}
}  // namespace argcv::wrapper::ini
