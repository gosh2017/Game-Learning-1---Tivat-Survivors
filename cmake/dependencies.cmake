# ��������

# ʹ��FetchContent��������
include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# ��������...
# find_package(Boost COMPONENTS filesystem system REQUIRED)