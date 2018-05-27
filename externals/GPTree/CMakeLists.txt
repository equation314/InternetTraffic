
FILE(GLOB SRCS *.cpp *.h)
add_library(gptree ${SRCS})
target_link_libraries(gptree metis)
