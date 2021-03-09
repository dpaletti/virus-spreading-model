cmake_minimum_required(VERSION 3.10)

project (virus-spreading-model VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(virus-spreading-model main.cpp Country.cpp Country.h World.cpp World.h Point.cpp Point.h set_countries_anchor_point.cpp Cell.cpp Cell.h Grid.cpp Grid.h)

find_package(MPI REQUIRED)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(virus-spreading-model PUBLIC MPI::MPI_CXX)