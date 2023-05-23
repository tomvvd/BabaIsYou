cmake_minimum_required(VERSION 3.5)


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
)

install(TARGETS BabaIsYou
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
