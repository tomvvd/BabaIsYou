cmake_minimum_required(VERSION 3.5)

add_executable(BabaIsYouTests

    testPosition.cpp
    testGame.cpp
    testLevelLoader.cpp
    ../src/game/Position.h
    ../src/game/Position.cpp
    ../src/game/EntityNature.h
    ../src/game/EntityType.h
    ../src/util/Observer.h
    ../src/util/Observable.h
    ../src/util/Observer.cpp
    ../src/util/Observable.cpp
    ../src/game/Rule.h
    ../src/game/Rule.cpp
    ../src/console/View.h
    ../src/console/View.cpp
    ../src/console/Controller.h
    ../src/console/Controller.cpp
    ../src/game/LevelLoader.h
    ../src/game/LevelLoader.cpp
    ../src/game/Game.h
    ../src/game/Game.cpp
    ../src/game/Board.h
    ../src/game/Board.cpp
    ../src/game/Entity.h
    ../src/game/Entity.cpp
    ../src/game/Direction.h
)
target_include_directories(BabaIsYouTests PRIVATE
    ../src
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

target_link_libraries(BabaIsYouTests Catch2::Catch2WithMain)
