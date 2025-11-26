cmake_minimum_required(VERSION 3.10)
project(FinanceTracker)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")
add_executable(FinanceTracker ${SOURCES})

target_include_directories(FinanceTracker PRIVATE src)

set(SFML_DIR "D:/Libraries/SFML-3.0.0/lib/cmake/SFML")
find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window)

target_link_libraries(FinanceTracker PRIVATE
    SFML::Graphics
    SFML::Window
)

add_custom_command(
    TARGET FinanceTracker
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:FinanceTracker>/data"
)

add_custom_command(
    TARGET FinanceTracker
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:FinanceTracker>/assets"
)

add_custom_command(TARGET FinanceTracker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:"${SFML_DIR}/../../../bin/sfml-graphics-d-3.dll">
        $<$<CONFIG:Debug>:"${SFML_DIR}/../../../bin/sfml-window-d-3.dll">
        $<$<CONFIG:Debug>:"${SFML_DIR}/../../../bin/sfml-system-d-3.dll">
        $<$<CONFIG:Debug>:"${SFML_DIR}/../../../bin/sfml-audio-d-3.dll">
        $<$<CONFIG:Debug>:"${SFML_DIR}/../../../bin/sfml-network-d-3.dll">
        $<$<CONFIG:Release>:"${SFML_DIR}/../../../bin/sfml-graphics-3.dll">
        $<$<CONFIG:Release>:"${SFML_DIR}/../../../bin/sfml-window-3.dll">
        $<$<CONFIG:Release>:"${SFML_DIR}/../../../bin/sfml-system-3.dll">
        $<$<CONFIG:Release>:"${SFML_DIR}/../../../bin/sfml-audio-3.dll">
        $<$<CONFIG:Release>:"${SFML_DIR}/../../../bin/sfml-network-3.dll">
        $<TARGET_FILE_DIR:FinanceTracker>)
