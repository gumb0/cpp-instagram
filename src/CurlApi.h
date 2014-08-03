#ifndef CPP_INSTAGRAM_IMPL_CURL_API_H
#define CPP_INSTAGRAM_IMPL_CURL_API_H

#include <curl/curl.h>
#include <memory>

namespace Instagram
{
    typedef size_t (*WriteCallback)(char* ptr, size_t size, size_t nmemb, void* userdata);

    // The virtual interface wrapper over libcurl, it is needed to mock libcurl calls in unit tests
    class CurlApi
    {
    public:
        virtual ~CurlApi() {}

        virtual CURLcode curl_global_init(long flags) = 0;
        virtual void curl_global_cleanup() = 0;
        virtual CURL* curl_easy_init() = 0;
        virtual void curl_easy_cleanup (CURL* handle) = 0;
        virtual CURLcode curl_easy_setopt_string(CURL* handle, CURLoption option, const char* parameter) = 0;
        virtual CURLcode curl_easy_setopt_long(CURL* handle, CURLoption option, long parameter) = 0;
        virtual CURLcode curl_easy_setopt_func(CURL* handle, CURLoption option, WriteCallback parameter) = 0;
        virtual CURLcode curl_easy_setopt_ptr(CURL* handle, CURLoption option, void* parameter) = 0;
        virtual CURLcode curl_easy_perform(CURL* handle) = 0;
    };

    typedef std::shared_ptr<CurlApi> CurlApiPtr;

}

#endif