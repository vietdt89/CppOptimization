cmake_minimum_required(VERSION 3.10)

project(TestService)

SET(
	CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Thêm tệp nguồn cho tệp thực thi
SET ( SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/test_service.cpp
)

add_executable(test_service ${SOURCE})
target_link_libraries(test_service binder pthread iconfiguration iapplication)