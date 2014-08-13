#include "Exception.h"
#include "ServerResponse.h"

#include <gmock/gmock.h>

using namespace Instagram;
using namespace testing;

class ParsingUserResponseTest : public Test
{
    virtual void SetUp()
    {
        const std::string json = R"({"meta":{"code":200},"data":{"username":"snoopdogg","bio":"I smoked out the whitehouse !","website":"http://bit.ly/1onGzhG","profile_picture":"http://images.ak.instagram.com/profiles/profile_1574083_75sq_1381898834.jpg", "full_name":"Snoop Dogg", "counts" : {"media":7453, "followed_by" : 3370805, "follows" : 698}, "id" : "1574083"}})";
        ServerResponse response;

        userInfo = response.parseUser(json);
    }

protected:
    UserInfo userInfo;
};

TEST_F(ParsingUserResponseTest, ParsesId)
{
    ASSERT_THAT(userInfo.mId, StrEq("1574083"));
}

TEST_F(ParsingUserResponseTest, ParsesUsername)
{
    ASSERT_THAT(userInfo.mUsername, StrEq("snoopdogg"));
}

TEST_F(ParsingUserResponseTest, ParsesFullName)
{
    ASSERT_THAT(userInfo.mFullName, StrEq("Snoop Dogg"));
}

TEST_F(ParsingUserResponseTest, ParsesProfilePicture)
{
    ASSERT_THAT(userInfo.mProfilePicture, StrEq("http://images.ak.instagram.com/profiles/profile_1574083_75sq_1381898834.jpg"));
}

class ParsingIncorrectUserResponseTest : public Test
{
protected:
    ServerResponse response;
};

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfJsonParseFails)
{
    const std::string json = "{meta";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoData)
{
    const std::string json = R"({"meta":{"code":200}})";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoId)
{
    const std::string json = R"({"meta":{"code":200},"data":{"username":"snoopdogg"}})";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfResponseIsError)
{
    const std::string json = R"({"meta":{"error_type": "APINotAllowedError", "code": 400, "error_message": "you cannot view this resource"}})";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoUsername)
{
    const std::string json = R"({"meta":{"code": 200},"data":{"id": "1574083"}})";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoFullName)
{
    const std::string json = R"({"meta":{"code": 200},"data":{"id": "1574083", "username":"snoopdogg"}})";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}

TEST_F(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoProfilePicture)
{
    const std::string json = R"({"meta":{"code": 200},"data":{"id": "1574083", "username":"snoopdogg", "full_name": "snoopdogg"}})";

    ASSERT_THROW(response.parseUser(json), Instagram::Exception);
}
