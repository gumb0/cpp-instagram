#ifndef CPP_INSTAGRAM_IMPL_CURL_IMPL_H
#define CPP_INSTAGRAM_IMPL_CURL_IMPL_H

#include "Curl.h"
#include "CurlApi.h"

namespace Instagram
{
    class CurlImpl : public Curl
    {
    public:
        CurlImpl(CurlApiPtr curlApi);
        virtual ~CurlImpl();

        virtual std::string get(const std::string& url);

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

}

#endif
