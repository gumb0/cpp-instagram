#ifndef CPP_INSTAGRAM_IMPL_CURL_INITIALIZER_H
#define CPP_INSTAGRAM_IMPL_CURL_INITIALIZER_H

#include "CurlApi.h"

namespace Instagram
{
    class CurlInitializer
    {
    public:
        explicit CurlInitializer(CurlApiPtr curlApi);
        ~CurlInitializer();

    private:
        CurlApiPtr mCurlApi;
    };
}

#endif
