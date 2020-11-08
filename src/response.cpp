#include <socketer.h>
#include <string>
#include <map>
#include <list>
#include <memory.h>
#include <unistd.h>

namespace Socketer
{
    Response::Response(int socket)
    {
        this->socket = socket;
        this->currentWritePosition = 0;
        this->rawHeads = std::list<std::string>();
        this->headers = std::map<std::string, std::string>();

        this->memoryFrame = 512;
        this->currentBodySize = 512;
        this->responseBody = (char*) malloc(this->currentBodySize * sizeof(char));
        memset(this->responseBody, 0, sizeof(char) * this->currentBodySize);
    }

    void Response::reply()
    {
        for (auto it = this->rawHeads.begin(); it != this->rawHeads.end(); it++) {
            ::write(this->socket, (void*) it->c_str(), it->length());
            ::write(this->socket, (void*) "\r\n", 2);
        }

        char* header_row = (char*) malloc(512 * sizeof(char));

        for (auto it = this->headers.begin(); it != this->headers.end(); it++) {
            memset(header_row, 0, 512 * sizeof(char));
            sprintf(header_row, "%s: %s\r\n", it->first.c_str(), it->second.c_str());
            ::write(this->socket, header_row, strlen(header_row));
        }
        free(header_row);
        ::write(this->socket, (void*) "\r\n", 2);

        ::write(this->socket, this->responseBody, this->currentWritePosition);
    }

    void Response::writeHead(std::string rawHead)
    {
        this->rawHeads.emplace_back(std::move(rawHead));
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
