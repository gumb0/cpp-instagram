#ifndef CPP_INSTAGRAM_IMPL_CURL_H
#define CPP_INSTAGRAM_IMPL_CURL_H

#include <memory>
#include <string>

namespace Instagram
{
    class Curl
    {
    public:
        virtual ~Curl() {}

        virtual std::string get(const std::string& url) = 0;
    };

    typedef std::shared_ptr<Curl> CurlPtr;

}

#endif
