#ifndef SOCKETER_SOCKETER_H
#define SOCKETER_SOCKETER_H

#include <string>
#include <socketer/handler.h>

namespace Socketer
{
    class Socketer
    {
    public:
        Socketer();
        void addHandler(std::string uri, ServeHttpCallback callback);
        void dispatch();
        void listen(std::string host, int port);

    private:
        std::string listen_host;
        int listen_port;
    };
}

#endif
