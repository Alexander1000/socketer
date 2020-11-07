# socketer

## Example usage:
```cpp
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <socketer.h>

void on_default_request(Socketer::Request* request, int socket);
void on_request_v1_save(Socketer::Request* request, int socket);

int main(int argc, char** argv) {
    Socketer::Socketer server;

    server.listen("127.0.0.1", 50123);

    server.addHandler("/v1/save", on_request_v1_save);

    server.setDefaultHandler(on_default_request);

    server.dispatch();

    return 0;
}

void on_request_v1_save(Socketer::Request* request, int socket) {
    std::cout << "/v1/save called" << std::endl;

    std::string http_response = "HTTP/1.1 204 No Content\r\n";
    write(socket, http_response.c_str(), sizeof(char) * http_response.length());

    std::string http_server = "Server: some-server/1.0.0\r\n";
    write(socket, http_server.c_str(), sizeof(char) * http_server.length());

    write(socket, "\r\n\r\n", sizeof(char) * 4);
}

void on_default_request(Socketer::Request* request, int socket) {
    std::string http_response = "HTTP/1.1 204 No Content\r\n";
    write(socket, http_response.c_str(), sizeof(char) * http_response.length());

    std::string http_server = "Server: some-server/1.0.0\r\n";
    write(socket, http_server.c_str(), sizeof(char) * http_server.length());

    write(socket, "\r\n\r\n", sizeof(char) * 4);
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
