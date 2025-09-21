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

# Set output directories.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -g -W4 -Wall")
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /DEBUG")  # MSVC
endif()

# Add debugging information to the Release build type.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -W4 -Wall")  # GCC/Clang: Add debugging symbols.
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -g")  # The link also includes debugging information.
# Specific settings for MSVC.
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")  # Generate program database.
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG")  # Generate debugging information.
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG")  # Debugging information for DLL.
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /DEBUG")  # Debugging information for modules.
    
    # Ensure that PDB files and executable files are in the same directory (for easy debugging).
    set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    message(STATUS "Release setting ${CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE}")
endif()

# Include customized CMake module.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
#include(dependencies)  # Used for managing project dependencies

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
#install(DIRECTORY PixelGame/inc/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

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

# Install pdb files.
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
    DESTINATION ${CMAKE_INSTALL_BINDIR}/DebugInfo
    FILES_MATCHING
    PATTERN "*.pdb"
)

# Install resources files.
set(RESOURCE_DIRECTORY "Resources")
install(DIRECTORY ${RESOURCE_DIRECTORY}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${RESOURCE_DIRECTORY}
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)