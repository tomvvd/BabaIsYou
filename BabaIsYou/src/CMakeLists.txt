cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(BabaIsYou
    main.cpp
    Direction.h
    Position.h
    Position.cpp
    EntityType.h
    EntityNature.h
    Entity.h
    Entity.cpp
    Board.h
    Board.cpp
    LevelLoader.h
    LevelLoader.cpp
    Rule.h
    Rule.cpp
    Game.h
    Game.cpp
    Controller.h
    Controller.cpp
    View.h
    View.cpp
    Observable.h
    Observer.h
    Observable.cpp
    Observer.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
target_link_libraries(BabaIsYou PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS BabaIsYou
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
