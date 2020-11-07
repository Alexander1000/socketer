#ifndef SOCKETER_ROUTE_H
#define SOCKETER_ROUTE_H

#include <string>
#include <socketer/handler.h>

namespace Socketer
{
    class Route
    {
    public:
        Route(std::string uri, ServeHttpHandler handler);

    private:
        std::string uri;
        ServeHttpHandler handler;
    };
}

#endif
