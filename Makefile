GCC=$(shell which gcc)
CFLAGS=-Wall -std=gnu99 -pthread
# -Werror

ifeq ($(GCC), /usr/bin/gcc)
	CC=gcc
else
	CC=cc
endif

objs=src/server_main.c src/server_base.c src/server_sockets.c src/server_router.c src/server_handlers.c src/server_parser.c src/server_logger.c src/server_static.c src/server_signals.c src/server_threading.c

# Compile the C
server: 
	${CC} ${objs} ${CFLAGS} -o server

# Kill all running docker containers
docker-kill:
	docker kill $(docker ps -q)

# Build the docker image
docker:
	docker build . -t cgull

# Run the docker container interactively
docker-run:
	docker run -ti -p 9001:9001 cgull:latest

# Run the docker container headless
docker-run-background:
	docker run -p 9001:9001 cgull:latest

# Delete the generated binary
clean: 
	rm -f server