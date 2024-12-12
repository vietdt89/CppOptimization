cmake_minimum_required(VERSION 3.10)

project(LogLibrary)

# Thêm tệp nguồn
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
)

# Tạo thư viện chia sẻ
add_library(liblog SHARED ${SOURCES})

# Đặt phiên bản cho thư viện (tùy chọn)
set_target_properties(liblog PROPERTIES VERSION 1.0 SOVERSION 1 )

# Chỉ định các thư mục chứa tệp tiêu đề cần public
target_include_directories(liblog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})