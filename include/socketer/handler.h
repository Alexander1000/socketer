#ifndef SOCKETER_HEADER_H
#define SOCKETER_HEADER_H

#include <functional>
#include <socketer/request.h>

typedef std::function<void(Socketer::Request*, int)> ServeHttpHandler;

namespace Socketer
{
    void default_handler(Socketer::Request* request, int socket);
}

#endif
