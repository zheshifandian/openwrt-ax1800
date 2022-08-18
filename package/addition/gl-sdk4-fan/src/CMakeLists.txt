cmake_minimum_required(VERSION 3.0)

project(gl_fan C)

aux_source_directory(. SRCS)
add_executable(gl_fan ${SRCS})

install(
    TARGETS gl_fan
    DESTINATION gl_fan
)
