#include <socketer.h>

namespace Socketer
{
    void default_handler(Request* request, Response* resp)
    {
        resp->writeHead("HTTP/1.1 200 OK");
        resp->addHeader("Server", "socketer/1.0.0");
        resp->write((char*) "default handler", 15);
        resp->reply();
    }
}
