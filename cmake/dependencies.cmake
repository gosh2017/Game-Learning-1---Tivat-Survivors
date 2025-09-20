# 依赖管理

# 使用FetchContent管理依赖
include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# 其他依赖...
# find_package(Boost COMPONENTS filesystem system REQUIRED)