cmake_minimum_required(VERSION 3.10)

project(AppManagerProject)

INCLUDE_DIRECTORIES (
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

SET(
	CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Thêm tệp nguồn cho tệp thực thi
SET ( APPLICATION_SRC_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/AppManager_main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AppManager.cpp
)
# Tạo tệp thực thi
add_executable(ApplicationManagerService ${APPLICATION_SRC_FILES})

# Liên kết tệp thực thi với thư viện chia sẻ
target_link_libraries(ApplicationManagerService binder pthread iapplication iconfiguration)

