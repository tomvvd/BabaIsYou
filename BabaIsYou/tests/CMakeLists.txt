cmake_minimum_required(VERSION 3.5)

add_executable(BabaIsYouTests

    testPosition.cpp
    ../src/Position.h
    testLevelLoader.cpp
    ../src/LevelLoader.h
    testGame.cpp
    ../src/Game.h

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
