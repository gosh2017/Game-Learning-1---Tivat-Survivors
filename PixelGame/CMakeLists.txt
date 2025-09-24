cmake_minimum_required (VERSION 3.12)

project ("PixelGame" LANGUAGES CXX)

# Collect source files.
file(GLOB_RECURSE PIXELGAME_SOURCES src/*.cpp)
file(GLOB_RECURSE PIXELGAME_HEADERS inc/*.h)

add_library(${PROJECT_NAME} SHARED
${PIXELGAME_SOURCES} ${PIXELGAME_HEADERS})
add_library(PixelGameTry::${PROJECT_NAME} ALIAS PixelGame)

# Set dll version.(Selected)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME ${PROJECT_NAME}  # Same name in different platform for sure.
)

# Set default symbol visibility to hidden.(recommend)
target_compile_options(${PROJECT_NAME} PRIVATE 
    -fvisibility=hidden  # GCC/Clang
    # Use __declspec(dllexport) in Windows to control visibility.
)

# If necessary, compiler specific options can be added.
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DCORE_EXPORTS  # Used for exporting Windows DLLs.
    )
endif()

set(EASYX_LIB "${CMAKE_SOURCE_DIR}/EasyXLibs")

target_link_directories(${PROJECT_NAME} PRIVATE ${EASYX_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE msimg32)

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR})
    message(WARNING "Debug libraries not found at: ${CMAKE_CURRENT_BINARY_DIR}")
endif()

# Include dir.
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        src
)

# Compile options.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Install targets.
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install PDB file (MSVC debugging symbols)
#install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> 
#    DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

#install(DIRECTORY inc
#    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
#)

export(TARGETS ${PROJECT_NAME}
    FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
    NAMESPACE PixelGameTry::
)