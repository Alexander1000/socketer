#ifndef SOCKETER_ROUTE_H
#define SOCKETER_ROUTE_H

#include <string>
#include <socketer/handler.h>
#include <socketer/request.h>

namespace Socketer
{
    class Route
    {
    public:
        Route(std::string uri, ServeHttpHandler handler);
        bool match(Request *r);
        ServeHttpHandler getHandler();

    private:
        std::string uri;
        ServeHttpHandler handler;
    };
}

#endif
