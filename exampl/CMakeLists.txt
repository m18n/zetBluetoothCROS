cmake_minimum_required(VERSION 2.6)
project(ZETANDROID)
file(GLOB CPPS "*.cpp")

add_subdirectory(zetBluetoothCROS)
add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} ZETPROGRAM)
add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/zetprogram/ZETPROGRAM.dll
                ${CMAKE_CURRENT_BINARY_DIR}/ZETPROGRAM.dll)