#include <socketer.h>

namespace Socketer
{
    Socketer::Socketer()
    {
        // set defaults
        this->listen_host = "127.0.0.1";
        this->listen_port = 8890;
    }
}
