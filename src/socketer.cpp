#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <socketer.h>
#include <string>
#include <utility>
#include <list>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

namespace Socketer
{
    Socketer::Socketer()
    {
        // set defaults
        this->listen_host = "127.0.0.1";
        this->listen_port = 8890;

        this->server_backlog = 256;

        this->routes = std::list<Route>();

        this->default_handler = ::Socketer::default_handler;

        this->middlewares = std::list<ServeHttpHandler>();
    }

    int Socketer::dispatch()
    {
        int server_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (server_sock == -1) {
            std::cout << "Error socket(): " << ::strerror(errno) << std::endl;
            return 1;
        }

        u_short      port  = this->listen_port;
        const char * host  = this->listen_host.c_str();
        sockaddr_in  sa;
        bzero(&sa, sizeof(sa));
        int          on    = 1;
        sa.sin_family      = AF_INET;
        sa.sin_port        = htons(port);
        sa.sin_addr.s_addr = inet_addr(host);

        if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
            std::cout << "Error setsockopt(): " << ::strerror(errno) << std::endl;
            return 1;
        }

        // Bind server socket to ip:port
        if (::bind(server_sock, (const sockaddr*)&sa, sizeof(sa)) == -1) {
            std::cout << "Error bind(): " << ::strerror(errno) << " on: " << host << ":" << port << std::endl;
            return 1;
        }

        // Make server to listen
        if (::listen(server_sock, this->server_backlog) == -1) {
            std::cout << "Error listen(): " << ::strerror(errno) << std::endl;
            return 1;
        }

        int clilen = sizeof(struct sockaddr);
        struct sockaddr cli_addr;

        int newsockfd;

        while (true) {
            newsockfd = accept(server_sock, &cli_addr, (socklen_t*) &clilen);

            if (newsockfd < 0) {
                std::cout << "Error! On Accepting Request! i.e. requests limit crossed" << std::endl;
            }

            int pid = fork();
            if (pid == 0) {
                std::cout << "Spawn worker" << std::endl;

                int maxBufferSize = 4096;

                char buf[maxBufferSize];
                memset(buf, 0, maxBufferSize * sizeof(char));

                char* requestMessage = (char*) malloc(maxBufferSize);
                requestMessage[0] = '\0';

                int totalReceiveBytes = 0;

                while (strstr(requestMessage, "\r\n\r\n") == NULL) {
                    int recvd = recv(newsockfd, buf, maxBufferSize, 0);
                    if (recvd < 0) {
                        std::cout << "Error while receiving data" << std::endl;
                        return 2;
                    } else if (recvd == 0) {
                        break;
                    } else {
                        totalReceiveBytes += recvd;

                        buf[recvd] = '\0';
                        if (totalReceiveBytes > maxBufferSize) {
                            maxBufferSize *= 2;
                            requestMessage = (char*) realloc(requestMessage, maxBufferSize);
                        }
                    }

                    strcat(requestMessage, buf);
                }

                this->on_request(requestMessage, totalReceiveBytes, newsockfd);

                close(newsockfd);
                break;
            }
        }

        close(server_sock);

        return 0;
    }

    void Socketer::listen(std::string host, int port)
    {
        this->listen_host = std::move(host);
        this->listen_port = port;
    }

    void Socketer::addHandler(std::string uri, ServeHttpHandler handler)
    {
        this->routes.emplace_back(Route(std::move(uri), std::move(handler)));
    }

    void Socketer::on_request(char *raw_message, int received_bytes, int socket)
    {
        Request req(raw_message);
        Response resp(socket);

        for (auto it = this->routes.begin(); it != this->routes.end(); it++) {
            if (it->match(&req)) {
                ServeHttpHandler handler = it->getHandler();
                this->call_handler(&handler, &req, &resp);
                return;
            }
        }

        this->call_handler(&this->default_handler, &req, &resp);
    }

    void Socketer::setDefaultHandler(ServeHttpHandler handler) {
        this->default_handler = std::move(handler);
    }

    void Socketer::call_handler(ServeHttpHandler* handler, Request *req, Response *resp)
    {
        for (auto it = this->middlewares.begin(); it != this->middlewares.end(); it++) {
            (*it)(req, resp);
        }
        (*handler)(req, resp);
    }

    void Socketer::addMiddleware(ServeHttpHandler handler) {
        this->middlewares.emplace_back(std::move(handler));
    }
}
