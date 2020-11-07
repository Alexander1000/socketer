#include <socketer.h>
#include <string>
#include <utility>
#include <list>

namespace Socketer
{
    Socketer::Socketer()
    {
        // set defaults
        this->listen_host = "127.0.0.1";
        this->listen_port = 8890;

        this->routes = std::list<Route>();
    }

    void Socketer::dispatch()
    {
        // do dispatch
    }

    void Socketer::listen(std::string host, int port)
    {
        this->listen_host = std::move(host);
        this->listen_port = port;
    }

    void Socketer::addHandler(std::string uri, ServeHttpHandler handler)
    {
        this->routes.emplace_back(Route(uri, handler));
    }
}
