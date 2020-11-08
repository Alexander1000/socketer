#include <socketer.h>

namespace Socketer
{
    void default_handler(Request* request, Response* resp)
    {
        resp->writeHead("HTTP/1.1 204 No Content");
        resp->addHeader("Server", "socketer/1.0.0");
        resp->reply();
    }
}
