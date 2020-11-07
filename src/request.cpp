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
        this->parse_raw_request(raw_request);
    }

    void Request::parse_raw_request(char *raw_request)
    {
        // parse head (first line)

        int i = 0;
        while (raw_request[i++] != ' ') {}

        this->method = new char[i];
        memset(this->method, 0, sizeof(char) * i);
        memcpy(this->method, raw_request, sizeof(char) * (i - 1));

        int start = i;
        while (raw_request[i++] != ' ') {}
        this->uri = new char[i - start];
        memset(this->uri, 0, sizeof(char) * (i - start));
        memcpy(this->uri, raw_request + start, sizeof(char) * (i - start - 1));

        start = i;
        while (raw_request[i++] != '\n') {}
        this->protocol = new char[i - start];
        memset(this->protocol, 0, sizeof(char) * (i - start));
        memcpy(this->protocol, raw_request + start, sizeof(char) * (i - start - 1));

        // parse headers

        int cur_pos = i;
        int requestLength = strlen(raw_request);

        do {
            int start_pos_header_name = cur_pos;
            int j = start_pos_header_name;
            while (raw_request[j++] != ':') {}
            char *header_name;
            header_name = new char[j - start_pos_header_name];
            memset(header_name, 0, sizeof(char) * (j - start_pos_header_name));
            memcpy(header_name, raw_request + start_pos_header_name, sizeof(char) * (j - start_pos_header_name - 1));

            j++; // skip space

            int start_pos_header_value = j;
            while (raw_request[j++] != '\n') {}
            char *header_value;
            header_value = new char[j - start_pos_header_value];
            memset(header_value, 0, sizeof(char) * (j - start_pos_header_value));
            memcpy(header_value, raw_request + start_pos_header_value, sizeof(char) * (j - start_pos_header_value - 1));

            this->headers[std::string(header_name)] = std::string(header_value);

            cur_pos = j - 1;

            if (raw_request[cur_pos] == '\n' && raw_request[cur_pos + 1] == '\r') {
                break;
            }

            cur_pos++;

            if (cur_pos >= requestLength) {
                break;
            }
        } while(true);

        this->raw_body = new char[requestLength - cur_pos];
        memset(this->raw_body, 0, sizeof(char) * (requestLength - cur_pos));
        memcpy(this->raw_body, raw_request + cur_pos, (requestLength - cur_pos));
    }
}
