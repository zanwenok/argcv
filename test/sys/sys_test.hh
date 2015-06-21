#ifndef ARGCV_TEST_ARGCV_SYS_SYS_TEST_HH
#define ARGCV_TEST_ARGCV_SYS_SYS_TEST_HH
#include "../argcv_test.h"

#include <stdio.h>

#include <string>

#include "argcv/sys/dirs.h"

using namespace argcv::string;

int dir_trav(const char* path, int recu, int (*file_handle)(const char* file_name, int is_dir, void* user),
             void* user);

int test_case_dir_trav_handler(const char* file_name, int is_dir, void* user) {
    int* u_data = (int*)user;
    printf("path:%s is_dir:%s data:%d\n", file_name, is_dir ? "yes" : "no", *u_data);
    (*u_data)++;
    return !((*u_data) < 10);
}

static int test_case_dir_trav(int argc, char* argv[]) {
    printf("[test_case_dir_trav] start\n");
    //std::string path("/tmp");
    std::string path(".");
    int u_data = 0;
    dir_trav(path.c_str(),1,test_case_dir_trav_handler,&u_data);
    printf("[test_case_dir_trav] end\n");
    return 0;
}

#endif  // ARGCV_TEST_ARGCV_SYS_SYS_TEST_HH