#ifndef ARGCV_TEST_ARGCV_STRING_STRING_TEST_HH
#define ARGCV_TEST_ARGCV_STRING_STRING_TEST_HH
#include "../argcv_test.h"

#include <string>

#include "argcv/string/string.hh"
#include "argcv/string/hash.hh"
#include "argcv/string/uuid.hh"

using namespace argcv::string;

static int test_case_string_split(int argc, char* argv[]) {
    std::string s("abc def ghi");
    auto v = split(s, " ");
    TEST_CASE_EXPECT_EQ(v.size(), 3);
    TEST_CASE_EXPECT_EQ(v[0], std::string("abc"));
    TEST_CASE_EXPECT_EQ(v[1], std::string("def"));
    TEST_CASE_EXPECT_EQ(v[2], std::string("ghi"));
    return 0;
}

static int test_case_string_replace(int argc, char* argv[]) {
    std::string s("abc def ghi");
    auto v = replace(s, "abc", "def");
    v = replace(v, "f d", "_x_");
    TEST_CASE_EXPECT_EQ(v, std::string("de_x_ef ghi"));
    return 0;
}

static int test_case_uuid(int argc, char* argv[]) {
    uuid _uuid(2047);
    uuid _uuid1(_uuid.str());
    uuid _uuid2(_uuid.data());
    uuid _uuid3(_uuid.hex());
    printf("id0 : %s\n", _uuid.str().c_str());
    printf("id1 : %s\n", _uuid1.str().c_str());
    printf("id2 : %s\n", _uuid2.str().c_str());
    printf("id3 : %s\n", _uuid3.str().c_str());
    TEST_CASE_EXPECT_EQ(_uuid.str(), _uuid1.str());
    TEST_CASE_EXPECT_EQ(_uuid.str(), _uuid2.str());
    TEST_CASE_EXPECT_EQ(_uuid.str(), _uuid3.str());
    return 0;
}

static int test_case_stemmer(int argc, char* argv[]) {
    std::vector<std::string> elems = stemm_s("Data Mining一些 中\u00A0文的 控,制 is an analytic process designed to explore data (usually large amounts of data - typically business or market related - also known as big data) in search of consistent patterns and/or systematic relationships between variables, and then to validate the findings by applying the detected patterns to new");
    for(size_t i =  0 ; i < elems.size(); i ++ ) {
        //printf("%zu (%s):%lu\n",i,elems[i].c_str(),elems[i].length());
        printf("[%s] ",elems[i].c_str());
    }
    printf("\n");
    return 0;
}


#endif  // ARGCV_TEST_ARGCV_STRING_STRING_TEST_HH