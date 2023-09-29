file(GLOB SRC_FILES "*.cpp")

foreach (SRC ${SRC_FILES})
  GET_FILENAME_COMPONENT(EXEC_NAME ${SRC} NAME_WE)
  add_executable(${EXEC_NAME} ${SRC})
  target_link_libraries(${EXEC_NAME})
  # target_compile_options(${EXEC_NAME} PRIVATE -fsanitize=address)
  # target_link_options(${EXEC_NAME} PRIVATE -fsanitize=address)
endforeach ()
