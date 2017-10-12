FROM ubuntu:trusty
EXPOSE 9001
RUN apt-get update
WORKDIR /var/www
COPY src/ /var/www
RUN ["make"]
ENTRYPOINT ["/var/www/server"]