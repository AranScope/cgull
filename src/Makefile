GCC=$(shell which gcc)
CFLAGS=-Wall -std=gnu99 -pthread
# -Werror

ifeq ($(GCC), /usr/bin/gcc)
	CC=gcc
else
	CC=cc
endif

objs=server_main.c server_base.c server_sockets.c server_router.c server_handlers.c server_parser.c server_logger.c server_static.c server_signals.c server_threading.c

# Compile the C
server: 
	${CC} ${objs} ${CFLAGS} -o server

# All target
all: 
	${CC} ${objs} ${CFLAGS} -o server

# Kill all running docker containers
docker-kill:
	docker kill $(docker ps -q)

# Build the docker image
docker:
	docker build ../ -t cgull

# Run the docker container interactively
docker-run:
	docker run -ti -p 9001:9001 cgull:latest

# Run the docker container headless
docker-run-background:
	docker run -p 9001:9001 cgull:latest

# Delete the generated binary
clean: 
	rm -f server