#ifndef SOCKETER_SOCKETER_H
#define SOCKETER_SOCKETER_H

#include <string>
#include <socketer/handler.h>
#include <socketer/route.h>
#include <list>

namespace Socketer
{
    class Socketer
    {
    public:
        Socketer();
        void addHandler(std::string uri, ServeHttpHandler handler);
        int dispatch();
        void listen(std::string host, int port);

    private:
        std::string listen_host;
        int listen_port;
        std::list<Route> routes;
        ServeHttpHandler default_handler;
        int server_backlog;

        void on_request(char* raw_message, int received_bytes, int socket);
    };
}

#endif
