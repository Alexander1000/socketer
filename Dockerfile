FROM debian:buster-20201012

RUN apt-get update \
    && apt-get install -y \
        curl \
        unzip \
        g++ \
        make \
        cmake

# install cpp-unit-test library
RUN mkdir -p /tmp/cpp-utils \
    && cd /tmp/cpp-utils \
    && curl -LO "https://github.com/Alexander1000/cpp-unit-test/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd cpp-unit-test-master \
    && cmake . \
    && make \
    && make install

COPY . /app

WORKDIR /app

RUN cmake . && make && make install
