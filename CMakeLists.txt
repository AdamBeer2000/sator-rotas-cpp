cmake_minimum_required(VERSION 3.5)

project(2dPlaindroms2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(2dPlaindroms2 main.cpp
    wordnode.h wordnode.cpp
    worddictionary.h worddictionary.cpp
    radix.h
    wordrange.h wordrange.cpp
    resultwriter.h resultwriter.cpp
)

include(GNUInstallDirs)

find_package(cxxopts REQUIRED)

install(TARGETS 2dPlaindroms2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
