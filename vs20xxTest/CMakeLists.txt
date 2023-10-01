cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(chess_board)


add_executable(chess_board 
 ../src/bitboard.cpp
 ../src/bitboard.h
 ../src/magics.h
 ../src/misc.cpp
 ../src/misc.h
 ../src/movegen.cpp
 ../src/movegen.h
 ../src/position.cpp
 ../src/position.h
 ../src/pyfunc.cpp
 ../src/pyfunc.h
 ../src/tt.cpp
 ../src/tt.h
 ../src/types.h
 ../src/vsmain.cpp
)