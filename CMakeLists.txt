cmake_minimum_required(VERSION 3.0.0)
project(RougeOne VERSION 0.1.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE src/main.cpp src/Actor/Actor.cpp src/Actor/Actor.h src/Player/Player.h src/Player/Player.cpp)
add_executable(RougeOne ${SOURCE})

#add_executable(RougeOne src/main.cpp)
#target_include_directories(RougeOne PUBLIC include)

target_link_libraries(RougeOne ${CURSES_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
