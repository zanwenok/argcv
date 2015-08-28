SET(rapidjson_build "${CMAKE_CURRENT_BINARY_DIR}/rapidjson")

# FIND_LIBRARY( LEVELDB_LIBRARY_INFO  NAMES  leveldb PATHS "${PROJECT_BINARY_DIR}/lib" )
INCLUDE(ProcessorCount)
ProcessorCount(PROCESSOR_COUNT_VAL)


EXTERNALPROJECT_ADD(
    rapidjson_proj
    GIT_REPOSITORY https://github.com/yuikns/rapidjson.git
    #GIT_TAG master
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    SOURCE_DIR ${rapidjson_build}
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
#    INSTALL_COMMAND  sh -c "rsync -a ${rapidjson_build}/include/ ${PROJECT_BINARY_DIR}/include/"
#    INSTALL_COMMAND  sh -c "rsync -a ${rapidjson_build}/libleveldb.* ${PROJECT_BINARY_DIR}/lib/ && rsync -a ${rapidjson_build}/include/ ${PROJECT_BINARY_DIR}/include/"
)

SET(RAPID_JSON_INCLUDE_DIR ${rapidjson_build}/include)

