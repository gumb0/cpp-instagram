#ifndef CPP_INSTAGRAM_IMPL_CURL_API_IMPL_H
#define CPP_INSTAGRAM_IMPL_CURL_API_IMPL_H

#include "CurlApi.h"

namespace Instagram
{
    // The virtual interface wrapper over libcurl, it is needed to mock libcurl calls in unit tests
    class CurlApiImpl : public ICurlApi /* noncopyable? */
    {
    public:
        // ICurlApi methods
        virtual CURLcode curl_global_init(long flags)
        {
            return ::curl_global_init(flags);
        }

        virtual void curl_global_cleanup()
        {
            ::curl_global_cleanup();
        }

        virtual CURL* curl_easy_init()
        {
            return ::curl_easy_init();
        }

        virtual void curl_easy_cleanup(CURL* handle)
        {
            ::curl_easy_cleanup(handle);
        }

        virtual CURLcode curl_easy_setopt_string(CURL* handle, CURLoption option, const char* parameter)
        {
            return ::curl_easy_setopt(handle, option, parameter);
        }

        virtual CURLcode curl_easy_setopt_long(CURL* handle, CURLoption option, long parameter)
        {
            return ::curl_easy_setopt(handle, option, parameter);
        }

        virtual CURLcode curl_easy_setopt_func(CURL* handle, CURLoption option, WriteCallback parameter)
        {
            return ::curl_easy_setopt(handle, option, parameter);
        }

        virtual CURLcode curl_easy_setopt_ptr(CURL* handle, CURLoption option, void* parameter)
        {
            return ::curl_easy_setopt(handle, option, parameter);
        }

        virtual CURLcode curl_easy_perform(CURL* handle)
        {
            return ::curl_easy_perform(handle);
        }

    };

}

#endif