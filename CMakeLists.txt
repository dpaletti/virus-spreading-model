cmake_minimum_required(VERSION 3.10)

project (virus-spreading-model VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(virus-spreading src/main.cpp src/Country.cpp src/Country.h src/World.cpp src/World.h src/Point.cpp src/Point.h src/Cell.cpp src/Cell.h src/Grid.cpp src/Grid.h src/InputParser.cpp src/InputParser.h src/Individual.cpp src/Individual.h src/Infected.cpp src/Infected.h src/Contact.cpp src/Contact.h src/MpiHandler.cpp src/MpiHandler.h src/JsonHandler.cpp src/JsonHandler.h)

find_package(MPI REQUIRED)
find_package(RapidJSON)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(virus-spreading PUBLIC MPI::MPI_CXX)
