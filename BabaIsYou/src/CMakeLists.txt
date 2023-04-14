cmake_minimum_required(VERSION 3.5)


add_executable(BabaIsYou
    main.cpp
    Direction.h
    Position.h
    MyClass.cpp
    MyClass.h
    EntityType.h
    EntityNature.h
    Entity.h
)

install(TARGETS BabaIsYou
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
