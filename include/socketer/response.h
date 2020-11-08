#ifndef SOCKETER_RESPONSE_H
#define SOCKETER_RESPONSE_H

#include <string>
#include <map>
#include <list>

namespace Socketer
{
    class Response
    {
    public:
        Response(int socket);
        void write(void* buf, int nByte);
        void writeHead(std::string rawHead);
        void addHeader(std::string headerName, std::string headerValue);
        void reply();
    private:
        int socket;
        std::list<std::string> rawHeads;
        std::map<std::string, std::string> headers;
        int memoryFrame;
        int currentWritePosition;
        int currentBodySize;
        void* responseBody;
    };
}

#endif
