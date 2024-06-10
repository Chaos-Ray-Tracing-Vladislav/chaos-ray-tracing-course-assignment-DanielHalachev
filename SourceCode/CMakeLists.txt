cmake_minimum_required(VERSION 3.5.0)
project(RayTracer VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

add_library(Ray Ray.cpp Ray.h)
add_library(RayTracer RayTracer.cpp RayTracer.h)
add_library(Triangle Triangle.cpp Triangle.h)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC Ray)
target_link_libraries(main PUBLIC RayTracer)
target_link_libraries(main PUBLIC Triangle)
target_link_libraries(RayTracer PRIVATE Ray)
target_link_libraries(Triangle PRIVATE Ray)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
