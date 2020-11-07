#include <socketer.h>
#include <string>
#include <unistd.h>

namespace Socketer
{
    void default_handler(Request* request, int socket)
    {
        std::string http_response = "HTTP/1.1 204 No Content\n";
        write(socket, http_response.c_str(), sizeof(char) * http_response.length());

        std::string http_server = "Server: socketer/1.0.0\n";
        write(socket, http_server.c_str(), sizeof(char) * http_server.length());

        write(socket, "\n\r\n\r", sizeof(char) * 8);
    }
}
