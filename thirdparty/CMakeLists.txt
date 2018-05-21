execute_process (
    COMMAND bash -c "cd ../thirdparty/metis && make config prefix=../../../../build/ && make install"
)