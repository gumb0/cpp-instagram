#ifndef CPP_INSTAGRAM_IMPL_EXCEPTION_HELPERS_H
#define CPP_INSTAGRAM_IMPL_EXCEPTION_HELPERS_H

#include "Exception.h"

#include <curl/curl.h>

namespace Instagram
{
    std::string GetErrorMessage(ErrorCode error, const std::string& additionalMessage);
    std::string GetCurlErrorMessage(ErrorCode error, CURLcode curlError);

    inline void Throw(ErrorCode error, const std::string& additionalMessage = std::string())
    {
        throw Exception(error, GetErrorMessage(error, additionalMessage));
    }

    inline void ThrowCurl(ErrorCode error, CURLcode curlError)
    {
        throw Exception(error, GetCurlErrorMessage(error, curlError), curlError);
    }
}

#endif