
add_executable(test_semaphore test_semaphore.cpp)
target_link_libraries(test_semaphore cpp)
if(UNIX)
target_link_libraries(test_semaphore pthread)
endif()
