cmake_minimum_required(VERSION 3.0.0)
project(RogueOne VERSION 0.1.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE src/main.cpp src/Position/Position.h src/Position/Position.cpp src/Actor/Actor.cpp src/Actor/Actor.h src/Player/Player.h src/Player/Player.cpp src/Room/Room.h src/Room/Room.cpp src/Level/Level.h src/Level/Level.cpp src/Monster/Monster.h src/Monster/Monster.cpp  src/utils/utils.h src/utils/utils.cpp src/utils/combat.cpp)
add_executable(RogueOne ${SOURCE})

#add_executable(RogueOne src/main.cpp)
#target_include_directories(RogueOne PUBLIC include)

target_link_libraries(RogueOne ${CURSES_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
