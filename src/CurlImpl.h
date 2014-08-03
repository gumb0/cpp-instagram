#ifndef CPP_INSTAGRAM_IMPL_CURL_H
#define CPP_INSTAGRAM_IMPL_CURL_H

#include "CurlApi.h"

#include <string>

namespace Instagram
{
    class Curl
    {
    public:
        Curl(CurlApiPtr curlApi);
        ~Curl();

        std::string get(const std::string& url);

    private:
        static size_t onDataReceived(char* buffer, size_t size, size_t nmemb, void* context);

        void setUrl(const std::string& url);
        void setGetMethod();

        void setReceiveCallback(std::string& outResult);

        void perform();

    private:
        CurlApiPtr mCurlApi;
        CURL* mHandle;
    };

    typedef std::shared_ptr<Curl> CurlPtr;

}

#endif
