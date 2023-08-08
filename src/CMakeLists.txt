add_executable(json_obj json_obj.cpp)
target_link_libraries(json_obj PRIVATE nlohmann_json::nlohmann_json)
