cmake_minimum_required(VERSION 3.8)
project(winrt-install-demo CXX)

add_executable(winrt-install-demo src/main.cpp)
set_property(TARGET winrt-install-demo APPEND PROPERTY LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
set_property(TARGET winrt-install-demo PROPERTY CXX_STANDARD 17)
set_property(TARGET winrt-install-demo PROPERTY CXX_STANDARD_REQUIRED ON)
