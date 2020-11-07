#ifndef SOCKETER_H
#define SOCKETER_H

#include <string>

namespace Socketer
{
    class Socketer
    {
    public:
        Socketer();
        void addHandler(std::string uri, ServeHttpCallback callback);
        void dispatch();
    };
}

#endif
