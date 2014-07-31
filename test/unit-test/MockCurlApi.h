#ifndef CPP_INSTAGRAM_TEST_MOCK_CURL_API_H
#define CPP_INSTAGRAM_TEST_MOCK_CURL_API_H

#include "CurlApi.h"

#include <gmock/gmock.h>

class MockCurlApi: public Instagram::ICurlApi
{
public:
    MOCK_METHOD1(curl_global_init, CURLcode(long flags));
    MOCK_METHOD0(curl_global_cleanup, void());
    MOCK_METHOD0(curl_easy_init, CURL*());
    MOCK_METHOD1(curl_easy_cleanup, void(CURL*));
    MOCK_METHOD3(curl_easy_setopt_string, CURLcode(CURL* handle, CURLoption option, const char* parameter));
    MOCK_METHOD3(curl_easy_setopt_long, CURLcode(CURL* handle, CURLoption option, long parameter));
    MOCK_METHOD3(curl_easy_setopt_func, CURLcode(CURL* handle, CURLoption option, Instagram::WriteCallback parameter));
    MOCK_METHOD3(curl_easy_setopt_ptr, CURLcode(CURL* handle, CURLoption option, void* parameter));
    MOCK_METHOD1(curl_easy_perform, CURLcode(CURL* handle));
};

#endif