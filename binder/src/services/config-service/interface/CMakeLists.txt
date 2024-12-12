cmake_minimum_required(VERSION 3.10)

project(IConfigManager)

# Thêm thư mục chứa các tệp tiêu đề
include_directories(include)

# Thêm tệp nguồn
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IConfigurationManagerService.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IConfigurationManagerReceiver.cpp
)

# Tạo thư viện chia sẻ
add_library(iconfiguration SHARED ${SOURCES})

# Đặt phiên bản cho thư viện (tùy chọn)
set_target_properties(iconfiguration PROPERTIES VERSION 1.0 SOVERSION 1)

# Chỉ định các thư mục chứa tệp tiêu đề cần public
target_include_directories(iconfiguration PUBLIC include)

# link library
target_link_libraries(iconfiguration binder pthread liblog)