#ifndef CPP_INSTAGRAM_TEST_MOCK_CURL_H
#define CPP_INSTAGRAM_TEST_MOCK_CURL_H

#include "Curl.h"

#include <gmock/gmock.h>

class MockCurl : public Instagram::Curl
{
public:
    MOCK_METHOD1(get, std::string(const std::string& url));
    MOCK_METHOD2(download, void(const std::string& url, const std::string& localPath));
};

#endif