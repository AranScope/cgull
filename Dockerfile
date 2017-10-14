# Start building on the GCC image, this is a linux distro with gcc installed
FROM gcc:4.9

# Expose the internal port 9001
EXPOSE 9001

# Set the working directory to the webroot
WORKDIR /var/www

# Copy over all of the C files
COPY src/ .

# Build the project
RUN make

# Run the server
CMD ["./server"]