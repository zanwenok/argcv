SET(crfpp_build "${CMAKE_CURRENT_BINARY_DIR}/crfpp")

INCLUDE(ProcessorCount)
ProcessorCount(PROCESSOR_COUNT_VAL)


EXTERNALPROJECT_ADD(
    crfpp_proj
    GIT_REPOSITORY git@github.com:yuikns/crfpp.git
    GIT_TAG master
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ./configure
    SOURCE_DIR ${crfpp_build}
    # BINARY_DIR ${crfpp_build}
    BUILD_COMMAND make -j${PROCESSOR_COUNT_VAL}
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)


SET(CRFPP_INCLUDE_DIR ${crfpp_build})
SET(CRFPP_LIB_DIR ${crfpp_build}/.libs)

ADD_LIBRARY(crfpp SHARED IMPORTED)
SET_PROPERTY(TARGET crfpp PROPERTY IMPORTED_LOCATION ${crfpp_build}/.libs/${CMAKE_SHARED_LIBRARY_PREFIX}crfpp${CMAKE_SHARED_LIBRARY_SUFFIX})

MESSAGE(STATUS "ARGCV CRFPP SHARD " ${crfpp_build}/${CMAKE_SHARED_LIBRARY_PREFIX}crfpp${CMAKE_SHARED_LIBRARY_SUFFIX})

ADD_LIBRARY(crfpp_static STATIC IMPORTED)
SET_PROPERTY(TARGET crfpp_static PROPERTY IMPORTED_LOCATION ${crfpp_build}/.libs/${CMAKE_STATIC_LIBRARY_PREFIX}crfpp${CMAKE_STATIC_LIBRARY_SUFFIX})

MESSAGE(STATUS "ARGCV CRFPP STATIC " ${crfpp_build}/${CMAKE_STATIC_LIBRARY_PREFIX}crfpp${CMAKE_STATIC_LIBRARY_SUFFIX})

ADD_DEPENDENCIES(crfpp crfpp_proj)

ADD_DEPENDENCIES(crfpp_static crfpp_proj)





