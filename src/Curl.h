#ifndef CPP_INSTAGRAM_IMPL_CURL_H
#define CPP_INSTAGRAM_IMPL_CURL_H

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{
    class Curl : NonCopyable
    {
    public:
        // perform GET request and return response, throw in case of error
        virtual std::string get(const std::string& url) = 0;

        // perform GET request and save response to file with localPath, throw in case of error
        virtual void download(const std::string& url, const std::string& localPath) = 0;
    };

    typedef std::shared_ptr<Curl> CurlPtr;

}

#endif
