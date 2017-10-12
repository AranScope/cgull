FROM gcc:4.9
EXPOSE 9001

WORKDIR /var/www
RUN mkdir build
COPY src/ .
RUN make
COPY content build/content

WORKDIR /var/www/build
CMD ["./server"]