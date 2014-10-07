#include "UrlBuilder.h"

#include <gmock/gmock.h>

using namespace Instagram;
using namespace testing;

class UrlBuilderTest : public Test
{
protected:
    std::string baseUrl{ "http://example.com/" };
    std::string path{ "some/path" };
    UrlBuilder urlBuilder{ baseUrl, path };
};

TEST_F(UrlBuilderTest, BuildsUrlWithoutQuery)
{
    ASSERT_THAT(urlBuilder.getResult(), StrEq(baseUrl + path));
}

TEST_F(UrlBuilderTest, BuildsUrlWithoutOneParam)
{
    const std::string key1 = "param1";
    const std::string value1 = "value1";

    urlBuilder.addParam(key1, value1);

    ASSERT_THAT(urlBuilder.getResult(), StrEq(baseUrl + path + "?" + key1 + "=" + value1));
}

TEST_F(UrlBuilderTest, BuildsUrlWithoutTwoParams)
{
    const std::string key1 = "param1";
    const std::string value1 = "value1";
    const std::string key2 = "param2";
    const std::string value2 = "value2";

    urlBuilder.addParam(key1, value1);
    urlBuilder.addParam(key2, value2);

    ASSERT_THAT(urlBuilder.getResult(), StrEq(baseUrl + path + "?" + key1 + "=" + value1 + "&" + key2 + "=" + value2));
}

TEST_F(UrlBuilderTest, BuildsUrlWithIntParam)
{
    const std::string key1 = "param1";
    const int value1 = 100;

    urlBuilder.addParam(key1, value1);

    ASSERT_THAT(urlBuilder.getResult(), StrEq(baseUrl + path + "?" + key1 + "=" + std::to_string(value1)));
}
