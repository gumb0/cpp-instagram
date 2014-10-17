#ifndef CPP_INSTAGRAM_TEST_MOCK_STDIO_API_H
#define CPP_INSTAGRAM_TEST_MOCK_STDIO_API_H

#include "StdioApi.h"

#include <gmock/gmock.h>

class MockStdioApi : public Instagram::StdioApi
{
public:
    MOCK_METHOD1(openFileForWrite, FILE*(const std::string& path));
    MOCK_METHOD1(closeFile, void(FILE*));
};

#endif