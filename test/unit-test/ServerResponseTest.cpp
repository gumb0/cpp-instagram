#include "Exception.h"
#include "Media.h"
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
    ASSERT_THAT(userInfo.mCounts, Field(&UserCounts::mMedia, 7453));
}

TEST_F(ParsingUserResponseTest, ParsesCountsFollows)
{
    ASSERT_THAT(userInfo.mCounts, Field(&UserCounts::mFollows, 698));
}

TEST_F(ParsingUserResponseTest, ParsesCountsFollowedBy)
{
    ASSERT_THAT(userInfo.mCounts, Field(&UserCounts::mFollowedBy, 3370805));
}

TEST(ParsingIncorrectUserResponseTest, ThrowsIfJsonHasNoId)
{
    ServerResponse response(R"({"meta":{"code":200},"data":{"username":"snoopdogg"}})");

    ASSERT_THROW(response.parseUser(), Instagram::Exception);
}

class ParsingFeedResponseTest : public Test
{
    virtual void SetUp()
    {
        const std::string json = R"({ "meta":{"code": 200}, "data":[{ "location": { "id": "833", "latitude" : 37.77956816727314, "longitude" : -122.41387367248539,
        "name" : "Civic Center BART" }, "comments": { "count": 0, "data" : [] }, "caption" : null, "link" : "http://instagr.am/p/BXsFz/",
            "likes" : { "count": 0, "data" : [] }, "created_time": "1296748524", "images" : { "low_resolution": 
            { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_6.jpg", "width" : 306, "height" : 306 },
            "thumbnail" : { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_5.jpg", "width" : 150, "height" : 150 },
            "standard_resolution" : { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_7.jpg", "width" : 612, "height" : 612 } },
            "type": "image", "users_in_photo" : [], "filter" : "Earlybird", "tags" : [], "id" : "22987123", "user" : { "username": "kevin",
            "full_name" : "Kevin S", "profile_picture" : "http://distillery.s3.amazonaws.com/profiles/profile_3_75sq_1295574122.jpg",
            "id" : "3" } } ] })";

        ServerResponse response(json);

        feed = response.parseFeed();
    }

protected:
    Feed feed;
};

TEST_F(ParsingFeedResponseTest, ParsesAllItems)
{
    ASSERT_THAT(feed, SizeIs(1));
}

TEST_F(ParsingFeedResponseTest, ParsesLink)
{
    ASSERT_THAT(feed[0]->getLink(), StrEq("http://instagr.am/p/BXsFz/"));
}
