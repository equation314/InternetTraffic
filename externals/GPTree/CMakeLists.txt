set(SRCS GPTree.cpp)

add_library(gptree ${SRCS})
target_link_libraries(gptree metis)
