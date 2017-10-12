CLANG=$(shell which clang)
CFLAGS=-Wall -Werror -std=gnu99 ../build

ifeq ($(CLANG), /usr/bin/clang)
	CC=clang
else
	CC=cc
endif


objs=server_main.o server_base.o server_sockets.o server_router.o server_handlers.o server_parser.o server_logger.o server_static.o server_signals.o

server: ${objs} ${CC] -o ${CFLAGS}