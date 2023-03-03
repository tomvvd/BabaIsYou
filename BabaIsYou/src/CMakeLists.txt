cmake_minimum_required(VERSION 3.5)


add_executable(BabaIsYou
    main.cpp
    MyClass.h
    MyClass.cpp
)

install(TARGETS BabaIsYou
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
