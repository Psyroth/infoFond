project(proj)

# Nécessaire pour que Minisat compile
add_executable(proj
    minisat/Solver.cpp
    main.cpp
    parser1.cpp
    problem1.cpp
    parser2.cpp
    problem2.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

