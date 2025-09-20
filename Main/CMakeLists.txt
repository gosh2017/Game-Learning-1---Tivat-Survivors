# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)

project (Main LANGUAGES CXX)

# Collect source files.
file(GLOB_RECURSE MAIN_SOURCES src/*.cpp)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "src/main.cpp")

# Include dir.
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Dependencies.
target_link_libraries(${PROJECT_NAME} PRIVATE 
    PixelGame
)

# 在 Windows 上，确保运行时能找到 DLL
#if(WIN32)
#    # 方法1：将 DLL 复制到可执行文件目录
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#            $<TARGET_FILE:PixelGame>
#            $<TARGET_FILE_DIR:${PROJECT_NAME}>
#        COMMENT "Copying PixelGame DLL to output directory"
#    )
#    
#    # 方法2：设置环境变量（用于调试）
#    # set_target_properties(app1 PROPERTIES
#    #     VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}/bin;$ENV{PATH}"
#    # )
#endif()

# Install tagrgets.
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
