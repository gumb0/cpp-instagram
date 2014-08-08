#include "CurlImpl.h"
#include "CurlInitializer.h"
#include "Exception.h"
#include "MockCurlApi.h"

#include <functional>
#include <gmock/gmock.h>

using namespace Instagram;
using namespace testing;

TEST(CurlInitializerTest, InitializesLibcurl)
{   
    std::shared_ptr<MockCurlApi> curlApi(new MockCurlApi);

    InSequence dummy;
    EXPECT_CALL(*curlApi, curl_global_init(_)).WillOnce(Return(CURLE_OK));
    EXPECT_CALL(*curlApi, curl_global_cleanup());

    CurlInitializer curlInit(curlApi);
}

TEST(CurlInitializerTest, ThrowsIfInitFails)
{
    std::shared_ptr<MockCurlApi> curlApi(new MockCurlApi);

    EXPECT_CALL(*curlApi, curl_global_init(_)).WillOnce(Return(CURLE_BAD_FUNCTION_ARGUMENT));

    std::unique_ptr<CurlInitializer> curlInitializer;
    ASSERT_THROW(curlInitializer.reset(new CurlInitializer(curlApi)), Instagram::Exception);
}

TEST(CurlConstructTest, ThrowsIfEasyInitFails)
{
    std::shared_ptr<MockCurlApi> curlApi(new MockCurlApi);

    EXPECT_CALL(*curlApi, curl_easy_init()).WillOnce(Return(static_cast<CURL*>(0)));

    CurlPtr curl;
    ASSERT_THROW(curl.reset(new CurlImpl(curlApi)), Instagram::Exception);
}

class CurlTest : public Test
{
protected:
    virtual void SetUp()
    {
        DefaultValue<CURLcode>::Set(CURLE_OK);

        curlApi.reset(new MockCurlApi);

        EXPECT_CALL(*curlApi, curl_easy_init()).WillOnce(Return(handle));

        curl.reset(new CurlImpl(curlApi));
    }

    virtual void TearDown()
    {
        EXPECT_CALL(*curlApi, curl_easy_cleanup(handle));

        curl.reset();

        DefaultValue<CURLcode>::Clear();
    }

    CURL* handle = reinterpret_cast<CURL*>(123);

    std::shared_ptr<MockCurlApi> curlApi;
    CurlPtr curl;
};

ACTION_P4(InvokeWriteCallback, callback, response, data, result)
{
    *result = callback(response, strlen(response), 1, data);
    return CURLE_OK;
}

TEST_F(CurlTest, PerformsGetRequest)
{
    std::string url = "http://example.com";
    EXPECT_CALL(*curlApi, curl_easy_setopt_string(handle, CURLOPT_URL, StrEq(url)));
    EXPECT_CALL(*curlApi, curl_easy_setopt_long(handle, CURLOPT_HTTPGET, 1));

    WriteCallback callback = 0;
    EXPECT_CALL(*curlApi, curl_easy_setopt_func(handle, CURLOPT_WRITEFUNCTION, _))
        .WillOnce(DoAll(SaveArg<2>(&callback), Return(CURLE_OK)));

    void* data = 0;
    EXPECT_CALL(*curlApi, curl_easy_setopt_ptr(handle, CURLOPT_WRITEDATA, _))
        .WillOnce(DoAll(SaveArg<2>(&data), Return(CURLE_OK)));
    
    char response[] = "response";
    size_t callbackResult = 0;
    EXPECT_CALL(*curlApi, curl_easy_perform(handle))
        // we need std::refs because these values will be set only inside curl_easy_perform, now values are empty
        .WillOnce(InvokeWriteCallback(std::ref(callback), response, std::ref(data), &callbackResult));
    
    std::string res = curl->get(url);

    ASSERT_THAT(res, StrEq(response));
    ASSERT_THAT(callbackResult, Eq(strlen(response)));
}

class CurlErrorsTest : public Test
{
protected:
    virtual void SetUp()
    {
        DefaultValue<CURLcode>::Set(CURLE_OK);

        curlApi.reset(new NiceMock<MockCurlApi>);

        EXPECT_CALL(*curlApi, curl_easy_init()).WillOnce(Return(reinterpret_cast<CURL*>(1)));
        curl.reset(new CurlImpl(curlApi));
    }

    virtual void TearDown()
    {
        DefaultValue<CURLcode>::Clear();
    }

    std::shared_ptr<MockCurlApi> curlApi;
    CurlPtr curl;
};

TEST_F(CurlErrorsTest, ThrowsIfSetUrlFails)
{
    EXPECT_CALL(*curlApi, curl_easy_setopt_string(_, CURLOPT_URL, _)).WillOnce(Return(CURLE_OUT_OF_MEMORY));

    ASSERT_THROW(curl->get(""), Instagram::Exception);
}

TEST_F(CurlErrorsTest, ThrowsIfSetGetMethodFails)
{
    EXPECT_CALL(*curlApi, curl_easy_setopt_long(_, CURLOPT_HTTPGET, _)).WillOnce(Return(CURLE_OUT_OF_MEMORY));

    ASSERT_THROW(curl->get(""), Instagram::Exception);
}

TEST_F(CurlErrorsTest, ThrowsIfSetWriteFunctionFails)
{
    EXPECT_CALL(*curlApi, curl_easy_setopt_func(_, CURLOPT_WRITEFUNCTION, _)).WillOnce(Return(CURLE_OUT_OF_MEMORY));

    ASSERT_THROW(curl->get(""), Instagram::Exception);
}

TEST_F(CurlErrorsTest, ThrowsIfSetWriteDataFails)
{
    EXPECT_CALL(*curlApi, curl_easy_setopt_ptr(_, CURLOPT_WRITEDATA, _)).WillOnce(Return(CURLE_OUT_OF_MEMORY));

    ASSERT_THROW(curl->get(""), Instagram::Exception);
}

TEST_F(CurlErrorsTest, ThrowsIfPerformFails)
{
    EXPECT_CALL(*curlApi, curl_easy_perform(_)).WillOnce(Return(CURLE_OUT_OF_MEMORY));

    ASSERT_THROW(curl->get(""), Instagram::Exception);
}
