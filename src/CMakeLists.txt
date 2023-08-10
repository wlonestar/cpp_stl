add_executable(timer timer.cpp)

add_executable(json_obj json_obj.cpp)
target_link_libraries(json_obj PRIVATE nlohmann_json::nlohmann_json)

add_executable(rbtree rbtree.cpp)
target_link_libraries(rbtree PRIVATE nlohmann_json::nlohmann_json)
