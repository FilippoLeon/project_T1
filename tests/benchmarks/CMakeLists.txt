macro(add_benchmark name)
	message(STATUS "New benchmark added: ${name}")
	add_executable(${name} ${name}.cpp)
	target_link_libraries(${name} PUBLIC gbench projectT1)
	# add_test(NAME ${name} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${name})
endmacro(add_benchmark)

add_benchmark(simple_kernels_benchmark) 

set(BENCHMARK_FORMAT "json" CACHE STRING "Output formad used by benchmark (one of json|console|csv).")

add_custom_target(run_all_tests COMMAND simple_kernels_benchmark --benchmark_format=${BENCHMARK_FORMAT} > f.json)