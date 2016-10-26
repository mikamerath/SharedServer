include_directories($TEST_SOURCE_DIR/source)
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(Test Test.cpp)
target_link_libraries(
Test
Game
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)