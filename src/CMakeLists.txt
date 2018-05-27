
FILE(GLOB SRCS *.cpp *.h)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(main ${SRCS})
target_link_libraries(main ${PYTHON_LIBRARIES} gptree)

add_library(engine SHARED ${SRCS})
target_link_libraries(engine ${PYTHON_LIBRARIES} gptree)
