# socketer

## Example usage:
```cpp
#include <string.h>
#include <iostream>

#include <socketer.h>

void on_default_request(Socketer::Request* request, Socketer::Response* response);
void on_request_v1_save(Socketer::Request* request, Socketer::Response* response);

int main(int argc, char** argv) {
    Socketer::Socketer server;

    server.listen("127.0.0.1", 50123);

    server.addHandler("/v1/save", on_request_v1_save);

    server.setDefaultHandler(on_default_request);

    server.dispatch();

    return 0;
}

void on_request_v1_save(Socketer::Request* request, Socketer::Response* response) {
    std::cout << "/v1/save called" << std::endl;

    response->writeHead("HTTP/1.1 204 No Content");
    response->addHeader("Server", "some-server/1.0.0");
    response->reply();
}

void on_default_request(Socketer::Request* request, Socketer::Response* response) {
    response->writeHead("HTTP/1.1 204 No Content");
    response->addHeader("Server", "some-server/1.0.0");
    response->reply();
}

```

## How it build:
```shell
cmake .
make
make install
```

## Build and run tests in docker
```shell
docker build -t socketer .
docker run --rm -it socketer
```
