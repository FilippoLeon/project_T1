include(ExternalProject)

find_package(Threads REQUIRED)

ExternalProject_Add(
        googletest
        PREFIX              "gtest"
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
		CMAKE_ARGS          "-Dgtest_force_shared_crt=ON"
        UPDATE_COMMAND      ""
        INSTALL_COMMAND     ""
        LOG_DOWNLOAD        ON
        LOG_CONFIGURE       ON
        LOG_BUILD           ON
)

set(GTEST_LIBRARY gtest)

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH "${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${CMAKE_FIND_LIBRARY_SUFFIXES}")
set(GTEST_LIBRARY_MAIN_PATH "${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${CMAKE_FIND_LIBRARY_SUFFIXES}")
set(GTEST_LIBRARY_MOCK_PATH "${binary_dir}/googlemock/${CMAKE_FIND_LIBRARY_PREFIXES}gmockd${CMAKE_FIND_LIBRARY_SUFFIXES}")
set(GTEST_LIBRARY_MOCK_MAIN_PATH "${binary_dir}/googlemock/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_maind${CMAKE_FIND_LIBRARY_SUFFIXES}")
add_library(${GTEST_LIBRARY} STATIC IMPORTED GLOBAL)

#"${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${CMAKE_FIND_LIBRARY_SUFFIXES};

add_dependencies(${GTEST_LIBRARY} googletest)

# Hack to make sure directories exists before set_target_properties (otherwise CMake will complain)
file(MAKE_DIRECTORY ${source_dir}/googletest/include/)
file(MAKE_DIRECTORY ${binary_dir}}/googlemock/gtest/)

set_target_properties(${GTEST_LIBRARY} PROPERTIES
        IMPORTED_LOCATION ${GTEST_LIBRARY_PATH}
        IMPORTED_LOCATION ${GTEST_LIBRARY_MAIN_PATH}
        IMPORTED_LOCATION ${GTEST_LIBRARY_MOCK_PATH}
        IMPORTED_LOCATION ${GTEST_LIBRARY_MOCK_MAIN_PATH}
        INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
        INTERFACE_LINK_LIBRARIES Threads::Threads)

ExternalProject_Add(
        googlebenchmark 
        PREFIX              "gbench"
        GIT_REPOSITORY      https://github.com/google/benchmark.git
        GIT_TAG             master
        CMAKE_ARGS          "-DBENCHMARK_ENABLE_GTEST_TESTS=OFF"
        UPDATE_COMMAND      ""
        INSTALL_COMMAND     ""
        LOG_DOWNLOAD        ON
        LOG_CONFIGURE       ON
        LOG_BUILD           ON
)
# -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON

ExternalProject_Get_Property(googlebenchmark source_dir)
set(GBENCH_INCLUDE_DIRS ${source_dir}/include)
ExternalProject_Get_Property(googlebenchmark binary_dir)
set(GBENCH_LIBRARY_PATH ${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}benchmark${CMAKE_FIND_LIBRARY_SUFFIXES})

set(GBENCH_LIBRARY gbench) 
add_library(${GBENCH_LIBRARY} STATIC IMPORTED GLOBAL)

add_dependencies(${GBENCH_LIBRARY} googlebenchmark)

# Hack to make sure directories exists before set_target_properties (otherwise CMake will complain)
file(MAKE_DIRECTORY ${source_dir}/include/)
file(MAKE_DIRECTORY ${binary_dir}/src/)

set_target_properties(${GBENCH_LIBRARY} PROPERTIES
        IMPORTED_LOCATION ${GBENCH_LIBRARY_PATH}
        INTERFACE_INCLUDE_DIRECTORIES ${GBENCH_INCLUDE_DIRS}
        INTERFACE_LINK_LIBRARIES "Threads::Threads;shlwapi")
