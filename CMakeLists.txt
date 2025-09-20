# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)
project(PixelGameTry
    VERSION 1.0.0
    DESCRIPTION "My C++ Project with multiple components"
    LANGUAGES CXX
)

# Set c++ standard.
set(CMAKE_CXX_STANDARD 17)         
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -g -W4 -Wall")

# Set output directories.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include customized CMake module.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
#include(dependencies)  # 用于管理项目依赖

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Default build type: Debug.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Include sub-projects.
add_subdirectory ("PixelGame")
add_subdirectory ("Main")

# If turn unit test on, add test dir.
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install configuration.
include(GNUInstallDirs)

# Install header files.
install(DIRECTORY PixelGame/inc/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#install(DIRECTORY core/inc/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export targets.
install(EXPORT PixelGame-targets
    FILE PixelGameTryCommonTargets.cmake
    NAMESPACE PixelGameTry::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PixelGameTry
)

# Package configuration.
include(CMakePackageConfigHelpers)

# Write version file.
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/PixelGameTryConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/PixelGameTryConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/PixelGameTryConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PixelGameTry
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/PixelGameTryConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/PixelGameTryConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PixelGameTry
)