#ifndef SOCKETER_REQUEST_H
#define SOCKETER_REQUEST_H

#include <string>
#include <map>

namespace Socketer
{
    class Request
    {
    public:
        Request(char* raw_request);
        char* method;
        char* uri;
        char* protocol;
        std::map<std::string, std::string> headers;
        char* raw_body;
    };
}

#endif
