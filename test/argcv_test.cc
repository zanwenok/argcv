#include "argcv_test.h"

#include <cstdio>
#include <cstring>

#include "string/string_test.hh"
#include "wrapper/leveldb_wr_test.hh"
#include "ir/index/analyzer/analyzer_test.hh"
#include "thread/threads_test.hh"
#include "argcv/argcv.hh"

static int test_case_info(int argc,char * argv[]) {
    argcv::argcv_info info;
    return 0;
}


const testcase_t test_list[] = {
    test_case_info,
    test_case_string_split,
    test_case_string_replace,
    test_case_uuid,
    test_case_analyzer_basic,
    test_case_leveldb_wr,
    test_case_threads
};

int main(int argc, char * argv[]) {
    TEST_CASE_EXPECT_GT(argc,1);
    int testmax = sizeof(test_list) / sizeof(test_list[0]);
    int offset = atoi(argv[1]);
    TEST_CASE_EXPECT_LT(offset,testmax);
    return test_list[offset](argc, argv);
}