project(tests)

add_subdirectory(lib)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)


add_executable(Google_Tests_run tests.cpp admin-tests.cpp date-tests.cpp platform-tests.cpp stream-tests.cpp user-tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)