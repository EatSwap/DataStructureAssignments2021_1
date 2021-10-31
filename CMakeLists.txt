CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(DataStructureAssignments2021_1)

SET(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -ffast-math -fomit-frame-pointer -march=native -mtune=native")

INCLUDE_DIRECTORIES(src)

ADD_EXECUTABLE(DataStructureAssignments2021_1
        src/main.cpp
        src/utils/random.cpp
        src/utils/utils.h
        src/airport/Runway.cpp
        src/airport/Runway.h
        src/airport/Plane.cpp
        src/airport/Plane.h
)
