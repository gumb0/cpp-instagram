#include "Exception.h"
#include "ServerResponse.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class ParsingIncorrectResponseTest : public Test
{

protected:
    std::unique_ptr<ServerResponse> response;
};

TEST_F(ParsingIncorrectResponseTest, ThrowsIfJsonParseFails)
{
    ASSERT_THROW(response.reset(new ServerResponse("{meta")), Instagram::Exception);
}

TEST_F(ParsingIncorrectResponseTest, ThrowsIfJsonHasNoData)
{
    ASSERT_THROW(response.reset(new ServerResponse(R"({"meta":{"code":200}})")), Instagram::Exception);
}

TEST_F(ParsingIncorrectResponseTest, ThrowsIfResponseIsError)
{
    ASSERT_THROW(response.reset(new ServerResponse(R"({"meta":{"error_type": "APINotAllowedError", "code": 400, "error_message": "you cannot view this resource"}})")), Instagram::Exception);
}


class ParsingUserResponseTest : public Test
{
    virtual void SetUp()
    {
        const std::string json = R"({"meta":{"code":200},"data":{"username":"snoopdogg","bio":"I smoked out the whitehouse !","website":"http://bit.ly/1onGzhG","profile_picture":"http://images.ak.instagram.com/profiles/profile_1574083_75sq_1381898834.jpg", "full_name":"Snoop Dogg", "counts" : {"media":7453, "followed_by" : 3370805, "follows" : 698}, "id" : "1574083"}})";
        ServerResponse response(json);

        userInfo = response.parseUser();
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

TEST_F(ParsingUserResponseTest, ParsesBio)
{
    ASSERT_THAT(userInfo.mBio, StrEq("I smoked out the whitehouse !"));
}

TEST_F(ParsingUserResponseTest, ParsesWebsite)
{
    ASSERT_THAT(userInfo.mWebsite, StrEq("http://bit.ly/1onGzhG"));
}

TEST_F(ParsingUserResponseTest, ParsesCountsMedia)
{
    ASSERT_THAT(userInfo.mCounts, Field(&UserCounts::media, 7453));
}

TEST_F(ParsingUserResponseTest, ParsesCountsFollows)
{
    ASSERT_THAT(userInfo.mCounts, Field(&UserCounts::follows, 698));
}

TEST_F(ParsingUserResponseTest, ParsesCountsFollowedBy)
{
    ASSERT_THAT(userInfo.mCounts, Field(&UserCounts::followedBy, 3370805));
}

TEST(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoData)
{
    ServerResponse response(R"({"meta":{"code":200},"data":{"username":"snoopdogg"}})");

    ASSERT_THROW(response.parseUser(), Instagram::Exception);
}
