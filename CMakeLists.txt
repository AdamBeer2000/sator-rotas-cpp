cmake_minimum_required(VERSION 3.5)

project(satorrotas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(satorrotas main.cpp
    wordnode.h wordnode.cpp
    worddictionary.h worddictionary.cpp
    radix.h
    wordrange.h wordrange.cpp
    exceptions.h
)

include(GNUInstallDirs)

add_subdirectory(lib/cxxopts)

install(TARGETS satorrotas
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
