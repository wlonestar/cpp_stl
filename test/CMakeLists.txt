file(GLOB SRC_FILES "*.cpp")

foreach (SRC ${SRC_FILES})
  GET_FILENAME_COMPONENT(EXEC_NAME ${SRC} NAME_WE)
  add_executable(${EXEC_NAME} ${SRC})
  target_link_libraries(${EXEC_NAME})
endforeach ()
