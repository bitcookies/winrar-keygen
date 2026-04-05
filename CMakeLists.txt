cmake_minimum_required(VERSION 3.16)
project(winrar-keygen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Version
set(APP_VERSION "4.1.0.0")

add_executable(winrar-keygen
    _tmain.cpp
    BigInteger.hpp
    EllipticCurveGF2m.hpp
    GaloisField.hpp
    Hasher.hpp
    HasherCrc32Traits.hpp
    HasherSha1Traits.hpp
    WinRarConfig.hpp
    WinRarKeygen.hpp
)

target_compile_definitions(winrar-keygen PRIVATE
    APP_VERSION="${APP_VERSION}"
)

# Find GMP
find_path(GMP_INCLUDE_DIR gmp.h REQUIRED)
target_include_directories(winrar-keygen PRIVATE ${GMP_INCLUDE_DIR})

# macOS Universal Binary support
if(APPLE AND CMAKE_OSX_ARCHITECTURES)
    message(STATUS "Building macOS Universal Binary: ${CMAKE_OSX_ARCHITECTURES}")
endif()

# Static linking on Linux for portable binaries
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(GMP_STATIC_LIBRARY libgmp.a)
    if(GMP_STATIC_LIBRARY)
        target_link_libraries(winrar-keygen PRIVATE ${GMP_STATIC_LIBRARY})
        target_link_options(winrar-keygen PRIVATE -static-libgcc -static-libstdc++)
        message(STATUS "Using static GMP: ${GMP_STATIC_LIBRARY}")
    else()
        find_library(GMP_LIBRARY gmp REQUIRED)
        target_link_libraries(winrar-keygen PRIVATE ${GMP_LIBRARY})
        message(STATUS "Using dynamic GMP: ${GMP_LIBRARY}")
    endif()
else()
    find_library(GMP_LIBRARY gmp REQUIRED)
    target_link_libraries(winrar-keygen PRIVATE ${GMP_LIBRARY})
endif()
