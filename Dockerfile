FROM debian:buster-20201012

RUN apt-get update \
    && apt-get install -y \
        g++ \
        make \
        cmake

COPY . /app

WORKDIR /app

RUN cmake . && make && make install
