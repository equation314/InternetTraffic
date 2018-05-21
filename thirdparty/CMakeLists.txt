set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_C_COMPILER /usr/local/bin/mpicc)
set(CMAKE_CXX_COMPILER /usr/local/bin/mpicxx)

set(METIS_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/libmetis.a)

set(CONFIG_PROGRAM make config prefix=../../../../build/)
set(BUILD_PROGRAM make install)

add_custom_target(config_metis ALL
        COMMAND ${CONFIG_PROGRAM}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/metis/
        COMMENT "Original metis makefile target")

add_custom_target(build_metis ALL
        COMMAND ${BUILD_PROGRAM}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/metis/
        COMMENT "Original metis makefile target")

add_library(metis STATIC IMPORTED)

set_property(TARGET metis APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(metis PROPERTIES IMPORTED_LOCATION_NOCONFIG "${METIS_LIBRARY}")

add_dependencies(metis build_metis)

execute_process (
    COMMAND g++ -std=c++0x -O2 ../thirdparty/GTree/src/gtree_new_p2p/GPTree.cpp -L/usr/local/lib/ -L./lib/ -I./include/ -lmetis -o gptree
)

execute_process (
    COMMAND g++ -std=c++0x -O2 -shared -fPIC ../thirdparty/GTree/src/gtree_new_p2p/GPTree.cpp -L/usr/local/lib/ -L./lib/ -I./include/ -lmetis -o lib/libgptree.so
)