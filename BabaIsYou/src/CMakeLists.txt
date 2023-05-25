cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(BabaIsYou
    main.cpp
    game/Direction.h
    game/Position.h
    game/Position.cpp
    game/EntityType.h
    game/EntityNature.h
    game/Entity.h
    game/Entity.cpp
    game/Board.h
    game/Board.cpp
    game/LevelLoader.h
    game/LevelLoader.cpp
    game/Rule.h
    game/Rule.cpp
    game/Game.h
    game/Game.cpp
    console/Controller.h
    console/Controller.cpp
    console/View.h
    console/View.cpp
    util/Observable.h
    util/Observer.h
    util/Observable.cpp
    util/Observer.cpp
    gui/mwbaba.ui
    gui/mwbaba.h
    gui/mwbaba.cpp
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
target_link_libraries(BabaIsYou PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS BabaIsYou
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
