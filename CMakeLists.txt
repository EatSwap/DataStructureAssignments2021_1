CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(DataStructureAssignments2021_1)

SET(CMAKE_CXX_STANDARD 23)

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
