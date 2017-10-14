cmake_minimum_required(VERSION 3.8)
project(cgull)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        list.h
        server_base.c
        server_base.h
        server_constants.h
        server_defines.h
        server_handlers.c
        server_handlers.h
        server_logger.c
        server_logger.h
        server_main.c
        server_main.h
        server_parser.c
        server_parser.h
        server_router.c
        server_router.h
        server_sockets.c
        server_sockets.h
        )

add_executable(cgull ${SOURCE_FILES})