#ifndef CPP_INSTAGRAM_EXCEPTION_H
#define CPP_INSTAGRAM_EXCEPTION_H

#include <string>

namespace Instagram
{
    //////////////////////////////////////////////////////////////////////////

    enum ErrorCode
    {
        CURL_GLOBAL_INIT_FAILED,
        CURL_EASY_INIT_FAILED,
        CURL_SETTING_URL_FAILED,
        CURL_SETTING_GET_METHOD_FAILED,
        CURL_SETTING_SSL_CERTIFICATE_PATH_FAILED,
        CURL_SETTING_WRITE_FUNCTION_FAILED,
        CURL_SETTING_WRITE_DATA_FAILED,
        CURL_PERFORM_FAILED,
        RESPONSE_JSON_PARSE_FAILED,
        RESPONSE_CONTAINS_SERVER_ERROR,
        USER_JSON_KEY_NOT_FOUND,
        UNKNOWN_MEDIA_TYPE,
        GET_VIDEOS_FROM_NOT_VIDEO_MEDIA,
        FILE_OPEN_FOR_WRITE_FAILED
    };

    //////////////////////////////////////////////////////////////////////////

    class Exception
    {
    public:
        Exception(ErrorCode errorCode, const std::string& message, int curlErrorCode = 0) :
            mErrorCode(errorCode),
            mMessage(message),
            mCurlErrorCode(curlErrorCode)
        {
        }

        int GetErrorCode() const
        {
            return mErrorCode;
        }

        std::string GetMessage() const
        {
            return mMessage;
        }
        
        int GetCurlErrorCode() const
        {
            return mCurlErrorCode;
        }

    private:
        const ErrorCode mErrorCode;
        const std::string mMessage;
        const int mCurlErrorCode;
    };
}

#endif