#include <socketer.h>
#include <string>
#include <map>
#include <memory.h>

namespace Socketer
{
    Response::Response(int socket)
    {
        this->socket = socket;
        this->currentWritePosition = 0;
        this->headers = std::map<std::string, std::string>();

        this->memoryFrame = 512;
        this->currentBodySize = 512;
        this->responseBody = (char*) malloc(this->currentBodySize * sizeof(char));
        memset(this->responseBody, 0, sizeof(char) * this->currentBodySize);
    }

    void Response::reply()
    {
        // do reply
    }

    void Response::addHeader(std::string headerName, std::string headerValue)
    {
        this->headers[std::move(headerName)] = std::move(headerValue);
    }

    void Response::write(void *buf, int nByte)
    {
        if (this->currentWritePosition + nByte >= this->currentBodySize) {
            int bytesLeft = nByte - (this->currentBodySize - this->currentWritePosition);
            int memoryCells = (bytesLeft / this->memoryFrame) + 1;
            this->responseBody = realloc(this->responseBody, this->currentBodySize + memoryCells * this->memoryFrame);
        }

        memcpy((char*) this->responseBody + this->currentWritePosition, buf, nByte);
        this->currentWritePosition += nByte;
    }
}
