#include <socketer.h>
#include <utility>

namespace Socketer
{
    Route::Route(std::string uri, ServeHttpHandler handler)
    {
        this->uri = std::move(uri);
        this->handler = std::move(handler);
    }

    bool Route::match(Request *r) {
        if (this->uri == r->uri) {
            return true;
        }

        return false;
    }
}
