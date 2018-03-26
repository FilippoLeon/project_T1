include(ExternalProject)

find_package(Threads REQUIRED)

ExternalProject_Add(
        googlebenchmark
        PREFIX              "gbench"
        GIT_REPOSITORY      https://github.com/google/benchmark.git
        GIT_TAG             master
        CMAKE_ARGS          "-DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON"
        UPDATE_COMMAND      ""
        INSTALL_COMMAND     ""
        LOG_DOWNLOAD        ON
        LOG_CONFIGURE       ON
        LOG_BUILD           ON
)

ExternalProject_Get_Property(googlebenchmark source_dir)
set(GBENCH_INCLUDE_DIRS ${source_dir}/include)
ExternalProject_Get_Property(googlebenchmark binary_dir)
set(GBENCH_LIBRARY_PATH ${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}benchmark.a)

set(GBENCH_LIBRARY gbench)
add_library(${GBENCH_LIBRARY} STATIC IMPORTED GLOBAL)

set_property(TARGET gbench PROPERTY DEPENDS googlebenchmark)

add_dependencies(${GBENCH_LIBRARY} googlebenchmark)

# Hack to make sure directories exists before set_target_properties (otherwise CMake will complain)
file(MAKE_DIRECTORY ${source_dir}/include/)
file(MAKE_DIRECTORY ${binary_dir}/src/)

set_target_properties(${GBENCH_LIBRARY} PROPERTIES
        IMPORTED_LOCATION ${GBENCH_LIBRARY_PATH}
        INTERFACE_INCLUDE_DIRECTORIES ${GBENCH_INCLUDE_DIRS}
        INTERFACE_LINK_LIBRARIES Threads::Threads)
