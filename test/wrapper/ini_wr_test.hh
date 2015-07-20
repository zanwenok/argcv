#ifndef ARGCV_TEST_WRAPPER_INI_WR_TEST_HH
#define ARGCV_TEST_WRAPPER_INI_WR_TEST_HH
#include "test/argcv_test.h"

#include <map>
#include <set>
#include <string>

#include "argcv/wrapper/ini_wr.hh"
using namespace argcv::string;
using namespace argcv::wrapper::ini;


static int test_case_ini_wr(int argc, char* argv[]) {
    ini_wr iw("config.ini");
    iw["a"]["0"] = 3.0;
    printf("value : %s \n",static_cast<std::string>(iw["a"]["0"]).c_str());
    printf("s1n1 : %s \n",static_cast<std::string>(iw["s1"]["n1"]).c_str());
    printf("s2n1 : %s \n",static_cast<std::string>(iw["s2"]["n1"]).c_str());
    printf("s2n2 : %s \n",static_cast<std::string>(iw["s2"]["n2"]).c_str());
    return 0;
}

#endif  // ARGCV_TEST_WRAPPER_INI_WR_TEST_HH