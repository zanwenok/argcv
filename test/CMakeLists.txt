ADD_EXECUTABLE(ctest_argcv argcv_test.cc)

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)
#MESSAGE(STATUS "ARGCV_EXECUTABLE_OUTPUT_PATH " ${EXECUTABLE_OUTPUT_PATH})

ADD_DEPENDENCIES(ctest_argcv argcv)

TARGET_LINK_LIBRARIES(ctest_argcv argcv_static)
TARGET_LINK_LIBRARIES(ctest_argcv argcv_sys_static)
TARGET_LINK_LIBRARIES(ctest_argcv argcv_wrapper_leveldb_static)
TARGET_LINK_LIBRARIES(ctest_argcv argcv_wrapper_ini_static)
TARGET_LINK_LIBRARIES(ctest_argcv pthread)

#  executable properties
SET_TARGET_PROPERTIES(ctest_argcv PROPERTIES OUTPUT_NAME ctest_argcv)


ADD_TEST(argcv_info ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 0)
ADD_TEST(argcv_string_split ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 1)
ADD_TEST(argcv_string_replace ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 2)
ADD_TEST(argcv_string_uuid ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 3)
ADD_TEST(argcv_ir_index_analyzer_basic ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 4)
ADD_TEST(argcv_wrapper_leveldb_wr ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 5)
ADD_TEST(argcv_wrapper_ini_wr ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 6)
ADD_TEST(argcv_threads ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 7)
ADD_TEST(argcv_dir_trav ${EXECUTABLE_OUTPUT_PATH}/ctest_argcv 8)

