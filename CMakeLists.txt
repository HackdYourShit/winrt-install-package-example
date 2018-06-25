cmake_minimum_required(VERSION 3.8)
project(cmake-demo CXX)

find_package(CURL REQUIRED)
find_package(OPENSSL REQUIRED)
find_package(ZLIB REQUIRED)

add_definitions("-DCURL_STATICLIB")
SET(CMAKE_CXX_FLAGS_RELEASE "/MT" CACHE STRING "" FORCE)

add_executable(cmake-demo src/main.cpp)
set_property(TARGET cmake-demo PROPERTY CXX_STANDARD 17)
set_property(TARGET cmake-demo PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(cmake-demo PRIVATE Ws2_32.lib Wldap32.lib ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES} ${CURL_LIBRARIES})
target_include_directories(cmake-demo PRIVATE ${CURL_INCLUDE_DIRS})
