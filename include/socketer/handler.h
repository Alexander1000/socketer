#ifndef SOCKETER_HEADER_H
#define SOCKETER_HEADER_H

#include <functional>
#include <socketer/request.h>
#include <socketer/response.h>

typedef std::function<void(Socketer::Request*, Socketer::Response*)> ServeHttpHandler;

namespace Socketer
{
    void default_handler(Socketer::Request* request, Socketer::Response* response);
}

#endif
