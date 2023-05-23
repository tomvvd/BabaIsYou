cmake_minimum_required(VERSION 3.5)

add_executable(BabaIsYouTests

    testPosition.cpp
    testGame.cpp
    testLevelLoader.cpp
    ../src/Position.h
    ../src/EntityNature.h
    ../src/EntityType.h
    ../src/Observer.h
    ../src/Observable.h
    ../src/Observer.cpp
    ../src/Observable.cpp
    ../src/Rule.h
    ../src/Rule.cpp
    ../src/View.h
    ../src/View.cpp
    ../src/Controller.h
    ../src/Controller.cpp
    ../src/Position.cpp
    ../src/LevelLoader.h
    ../src/LevelLoader.cpp
    ../src/Game.h
    ../src/Game.cpp
    ../src/Board.h
    ../src/Board.cpp
    ../src/Entity.h
    ../src/Entity.cpp
    ../src/Direction.h
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
