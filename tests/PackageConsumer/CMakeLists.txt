cmake_minimum_required(VERSION 3.25)

project(MCCPackageConsumer LANGUAGES CXX)

find_package(MCC 0.1 CONFIG REQUIRED)

add_executable(MCCPackageConsumer main.cpp)
target_link_libraries(MCCPackageConsumer PRIVATE MCC::MCC)

enable_testing()
add_test(NAME MCCPackageConsumer COMMAND MCCPackageConsumer)
