ADD_EXECUTABLE(argcv_test argcv_test.cc)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/test)

ADD_DEPENDENCIES(argcv_test argcv)

TARGET_LINK_LIBRARIES(argcv_test argcv_static)
TARGET_LINK_LIBRARIES(argcv_test argcv_sys_static)
TARGET_LINK_LIBRARIES(argcv_test argcv_wrapper_leveldb_static)
TARGET_LINK_LIBRARIES(argcv_test pthread)

#  executable properties
SET_TARGET_PROPERTIES(argcv_test PROPERTIES OUTPUT_NAME argcv_test)


ADD_TEST(argcv_info ${EXECUTABLE_OUTPUT_PATH}/argcv_test 0)
ADD_TEST(argcv_string_split ${EXECUTABLE_OUTPUT_PATH}/argcv_test 1)
ADD_TEST(argcv_string_replace ${EXECUTABLE_OUTPUT_PATH}/argcv_test 2)
ADD_TEST(argcv_string_uuid ${EXECUTABLE_OUTPUT_PATH}/argcv_test 3)
ADD_TEST(argcv_ir_index_analyzer_basic ${EXECUTABLE_OUTPUT_PATH}/argcv_test 4)
ADD_TEST(argcv_wrapper_leveldb_wr ${EXECUTABLE_OUTPUT_PATH}/argcv_test 5)
ADD_TEST(argcv_threads ${EXECUTABLE_OUTPUT_PATH}/argcv_test 6)
