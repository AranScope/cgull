# cgull
cgull is a multithreaded sever that has a subset of features from http 1.x.

## Run
The Makefile in `src/Makefile` has several main commands

```
# Compile the server into a binary in src/build
make

# Delete any previously generated binaries
make clean

# Create the docker image, this compiles the C internally
make docker

# Run the docker container headless 
make docker-run

# Run the docker container with a shell
make docker-run-interactive

# Kill all running docker containers
make docker-kill
```

The C binary accepts one argument -- A port specified as the first command line argument

```
cd src/build

# Defaults to port 9001 (this is used by docker also)
./server 

# Set the port manually
./server 8080
```