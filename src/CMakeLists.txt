set(SRCS InternetTraffic.cpp Car.cpp Map.cpp Solution.cpp Node.cpp)

add_library(itraffic ${SRCS})
target_link_libraries(itraffic gptree)

add_executable(main main.cpp)
target_link_libraries(main itraffic)
