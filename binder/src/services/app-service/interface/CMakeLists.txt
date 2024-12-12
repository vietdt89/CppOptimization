cmake_minimum_required(VERSION 3.10)

project(iapplication)

# Thêm thư mục chứa các tệp tiêu đề
include_directories(include)

# Thêm tệp nguồn
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IApplicationManagerService.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IApplicationManagerReceiver.cpp
)

# Tạo thư viện chia sẻ
add_library(iapplication SHARED ${SOURCES})

# Đặt phiên bản cho thư viện (tùy chọn)
set_target_properties(iapplication PROPERTIES VERSION 1.0 SOVERSION 1 )

# Chỉ định các thư mục chứa tệp tiêu đề cần public
target_include_directories(iapplication PUBLIC include)

# Link các thư viện thành phần khi build source
target_link_libraries(iapplication binder pthread liblog)