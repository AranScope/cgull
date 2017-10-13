# cgull
cgull is a multithreaded sever that has a subset of features from http 1.x.

## Features
- Containerisation using Docker
- Custom request routing inspired by node (found in `server_main.c`) e.g.
```Java
serve("./content");
route(GET, "/hello", text("Hello World!"));
route(GET, "/world", text("World!"));
```
- Custom logger with varying levels `debug, error, info` found in `server_logger.c`
- Multithreaded using pthread
- Dynamically add web pages without reloading
- Supports GET and HEAD requests

## Run
The Makefile in `src/Makefile` has several main commands

```Bash
# Compile the server into a binary in src/build
make

# Delete any previously generated binaries, required for regenerating new binary
make clean

# Create the docker image, this compiles the C internally
make docker

# Run the docker container in the background
make docker-run-background

# Run the docker container with a shell
make docker-run

# Kill all running docker containers (useful if running in background)
make docker-kill
```

The C binary accepts one argument -- A port specified as the first command line argument

```Bash
# Defaults to port 9001 (this is used by docker also)
./server 

# Set the port manually
./server 8080

# Use a port that requires higher priveledges
sudo ./server 80
```