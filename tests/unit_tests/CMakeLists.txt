macro(add_test_exec name)
	message(STATUS "New test added: ${name}")
	add_executable(${name} ${name}.cpp)
	target_link_libraries(${name} PUBLIC gtest INTERFACE projectT1)
	add_test(NAME ${name} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${name})
endmacro(add_test_exec)

add_test_exec(zip_test) 