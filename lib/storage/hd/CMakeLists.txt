SET(ARGCV_STORAGE_VERSION 1.0)
SET(ARGCV_STORAGE_SOVERSION 0.1)

AUX_SOURCE_DIRECTORY(. LIBARGCV_STORAGE_SRC)
ADD_LIBRARY(argcv_storage SHARED ${LIBARGCV_STORAGE_SRC})
SET_TARGET_PROPERTIES(argcv_storage PROPERTIES VERSION ${ARGCV_STORAGE_VERSION} SOVERSION ${ARGCV_STORAGE_SOVERSION})

ADD_LIBRARY(argcv_storage_static STATIC ${LIBARGCV_STORAGE_SRC})
SET_TARGET_PROPERTIES(argcv_storage_static PROPERTIES OUTPUT_NAME "argcv_storage")

ADD_DEPENDENCIES(argcv_storage argcv_wrapper_ini)
ADD_DEPENDENCIES(argcv_storage argcv_wrapper_leveldb)

TARGET_LINK_LIBRARIES(argcv_storage argcv_wrapper_leveldb)
TARGET_LINK_LIBRARIES(argcv_storage argcv_wrapper_ini)


ADD_DEPENDENCIES(argcv_storage_static argcv_wrapper_ini_static)
ADD_DEPENDENCIES(argcv_storage_static argcv_wrapper_leveldb_static)

TARGET_LINK_LIBRARIES(argcv_storage_static argcv_wrapper_leveldb_static)
TARGET_LINK_LIBRARIES(argcv_storage_static argcv_wrapper_ini_static)


