#ifndef ARGCV_TEST_ARGCV_TEST_HH
#define ARGCV_TEST_ARGCV_TEST_HH

#include <assert.h>

typedef int (*testcase_t)(int, char* []);

#define TEST_CASE_EXPECT_TRUE(a) assert(a != 0)
#define TEST_CASE_EXPECT_FALSE(a) assert(a == 0)
#define TEST_CASE_EXPECT_EQ(a, b) assert(a == b)
#define TEST_CASE_EXPECT_NE(a, b) assert(a == b)
#define TEST_CASE_EXPECT_LT(a, b) assert(a < b)
#define TEST_CASE_EXPECT_LE(a, b) assert(a <= b)
#define TEST_CASE_EXPECT_GT(a, b) assert(a > b)
#define TEST_CASE_EXPECT_GE(a, b) assert(a >= b)


#endif  // ARGCV_TEST_ARGCV_TEST_HH