include(FetchContent)
FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(vector_test vector_test.cpp)
target_link_libraries(vector_test gtest gtest_main pthread)

add_executable(list_test list_test.cpp)
add_executable(deque_test deque_test.cpp)

add_executable(stack_test stack_test.cpp)
target_link_libraries(stack_test gtest gtest_main pthread)

add_executable(queue_test queue_test.cpp)
target_link_libraries(queue_test gtest gtest_main pthread)

add_executable(tree_test tree_test.cpp)
target_link_libraries(tree_test gtest gtest_main pthread)
