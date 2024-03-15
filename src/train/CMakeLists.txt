# Building it
file(GLOB TRAIN_SRC_FILES *.cpp)
foreach(SRC_PATH ${TRAIN_SRC_FILES})
    get_filename_component(_target ${SRC_PATH} NAME_WE)

    include_directories(${DYNET_INCLUDE_DIR} ${PYBIND11_INCLUDE_DIR})

    add_executable(${_target} ${SRC_PATH})
    
    target_link_libraries(${_target} dynet pybind11::embed)
endforeach()
