FROM gcc:4.9
EXPOSE 9001

WORKDIR /var/www
RUN mkdir build
COPY src/ ./src
COPY Makefile .
RUN make
COPY content ./content

WORKDIR /var/www
CMD ["./server"]