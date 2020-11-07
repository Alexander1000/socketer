#include <socketer.h>
#include <string>
#include <map>

namespace Socketer
{
    Request::Request(char* raw_request)
    {
        // set defaults
        this->method = nullptr;
        this->uri = nullptr;
        this->protocol = nullptr;
        this->headers = std::map<std::string, std::string>();
        this->raw_body = nullptr;

        // parse request
    }
}
