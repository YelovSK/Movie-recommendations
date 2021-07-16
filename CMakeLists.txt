cmake_minimum_required(VERSION 3.17)
project(HodnotenieFilmov)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        ExceptionError.h
        1_Movie.h
        1_Movie.cpp
        2_AVL.h
        3_User.h
        3_User.cpp
        4_FilmDatabase.h
        4_FilmDatabase.cpp

        T1_TestMovie.cpp
        T2_TestAVL.cpp
        T3_TestUser.cpp
        T4_TestDatabase.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

include_directories(GoogleTest)
add_executable(HodnotenieFilmov ${SOURCE_FILES})
target_link_libraries(HodnotenieFilmov ${CMAKE_THREAD_LIBS_INIT})