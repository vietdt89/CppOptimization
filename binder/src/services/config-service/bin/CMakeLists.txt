cmake_minimum_required(VERSION 3.10)

project(ConfigManagerProject)

INCLUDE_DIRECTORIES (
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


SET(
	CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Thêm tệp nguồn cho tệp thực thi
SET ( CONFIG_SRC_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/ConfigManager_main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ConfigManager.cpp
)
# Tạo tệp thực thi
add_executable(ConfigurationManagerService ${CONFIG_SRC_FILES})

target_link_libraries(ConfigurationManagerService binder pthread stdc++fs iconfiguration iapplication liblog)