cmake_minimum_required(VERSION 3.0)

project(seakg-hack-xor C CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${seakg-hack-xor_SOURCE_DIR})

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/main.cpp")
list (APPEND WSJCPP_SOURCES "src/seakg_hack_xor.h")
list (APPEND WSJCPP_SOURCES "src/seakg_hack_xor.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (seakg-hack-xor ${WSJCPP_SOURCES})

target_link_libraries(seakg-hack-xor ${WSJCPP_LIBRARIES})

install(
    TARGETS
        seakg-hack-xor
    RUNTIME DESTINATION
        /usr/bin
)

