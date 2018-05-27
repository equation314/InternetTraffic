find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

set(SRCS itrafficpy.cpp)

add_library(itrafficpy SHARED ${SRCS})
target_link_libraries(itrafficpy ${PYTHON_LIBRARIES} itraffic)
