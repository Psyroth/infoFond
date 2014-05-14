project(proj)

# Nécessaire pour que Minisat compile
add_executable(proj
    minisat/Solver.cpp

    main.cpp
    parser.cpp
    problem.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

