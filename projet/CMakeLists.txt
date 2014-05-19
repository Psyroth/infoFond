project(proj)

# Nécessaire pour que Minisat compile
add_executable(Question1.bin 
    minisat/Solver.cpp
    main.cpp
    parser1.cpp
    problem1.cpp
    parser2.cpp
    problem2.cpp
    parser3.cpp
    problem3.cpp
)

add_executable(Question2.bin 
    minisat/Solver.cpp
    main.cpp
    parser1.cpp
    problem1.cpp
    parser2.cpp
    problem2.cpp
    parser3.cpp
    problem3.cpp
)

add_executable(Question3.bin 
    minisat/Solver.cpp
    main.cpp
    parser1.cpp
    problem1.cpp
    parser2.cpp
    problem2.cpp
    parser3.cpp
    problem3.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

