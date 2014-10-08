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
        const std::string json = R"({ "meta":{"code": 200 }, 
            "data":[
            { 
                "location": { 
                    "id": "833", 
                    "latitude" : 37.77956816727314, 
                    "longitude" : -122.41387367248539,
                    "name" : "Civic Center BART" 
                }, 
                "comments": { "count": 0, "data" : [] }, 
                "caption" : { 
                    "created_time": "1296710352", 
                    "text": "escalera", 
                    "from": { "username": "kevin", "full_name": "Kevin Systrom", "type": "user", "id": "3" },
                    "id": "26621408" }, 
                "link" : "http://instagr.am/p/BXsFz/",
                "likes" : { "count": 0, "data" : [] }, 
                "created_time": "1296748524", 
                "images" : { 
                    "low_resolution": { 
                        "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_6.jpg", 
                        "width" : 306, 
                        "height" : 306 },
                    "thumbnail" : { 
                        "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_5.jpg", 
                        "width" : 150, 
                        "height" : 150 },
                    "standard_resolution" : { 
                        "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_7.jpg", 
                        "width" : 612, 
                        "height" : 612 
                     } 
                },
                "type": "image", 
                "users_in_photo" : [], 
                "filter" : "Earlybird", 
                "tags" : [], 
                "id" : "22987123", 
                "user" : { 
                    "username": "kevin",
                    "full_name" : "Kevin S", 
                    "profile_picture" : "http://distillery.s3.amazonaws.com/profiles/profile_3_75sq_1295574122.jpg",
                    "id" : "3"
                 } 
            },
            {
                "videos": {
                    "low_resolution": {
                        "url": "http://distilleryvesper9-13.ak.instagram.com/090d06dad9cd11e2aa0912313817975d_102.mp4",
                        "width": 480,
                        "height": 480
                    },
                    "standard_resolution": {
                        "url": "http://distilleryvesper9-13.ak.instagram.com/090d06dad9cd11e2aa0912313817975d_101.mp4",
                        "width": 640,
                        "height": 640
                    }
                },
                "comments": {
                    "data": [{
                        "created_time": "1279332030",
                        "text": "Love the sign here",
                        "from": {
                            "username": "mikeyk",
                            "full_name": "Mikey Krieger",
                            "id": "4",
                            "profile_picture": "http://distillery.s3.amazonaws.com/profiles/profile_1242695_75sq_1293915800.jpg"
                        },
                        "id": "8"
                    },
                    {
                        "created_time": "1279341004",
                        "text": "Chilako taco",
                        "from": {
                            "username": "kevin",
                            "full_name": "Kevin S",
                            "id": "3",
                            "profile_picture": "..."
                        },
                        "id": "3"
                    }],
                    "count": 2
                },
                "caption": null,
                "likes": {
                    "count": 1,
                    "data": [{
                        "username": "mikeyk",
                        "full_name": "Mikeyk",
                        "id": "4",
                        "profile_picture": "..."
                    }]
                },
                "link": "http://instagr.am/p/D/",
                "created_time": "1279340983",
                "images": {
                    "low_resolution": {
                        "url": "http://distilleryimage2.ak.instagram.com/11f75f1cd9cc11e2a0fd22000aa8039a_6.jpg",
                        "width": 306,
                        "height": 306
                    },
                    "thumbnail": {
                        "url": "http://distilleryimage2.ak.instagram.com/11f75f1cd9cc11e2a0fd22000aa8039a_5.jpg",
                        "width": 150,
                        "height": 150
                    },
                    "standard_resolution": {
                        "url": "http://distilleryimage2.ak.instagram.com/11f75f1cd9cc11e2a0fd22000aa8039a_7.jpg",
                        "width": 612,
                        "height": 612
                    }
                },
                "type": "video",
                "users_in_photo": null,
                "filter": "Vesper",
                "tags": [],
                "id": "363839373298",
                "user": {
                    "username": "kevin",
                    "full_name": "Kevin S",
                    "profile_picture": "http://distillery.s3.amazonaws.com/profiles/profile_3_75sq_1295574122.jpg",
                    "id": "3"
                },
                "location": null
            } ] })";

        ServerResponse response(json);

        medias = response.parseFeed();
    }

protected:
    std::vector<MediaInfo> medias;
};

TEST_F(ParsingFeedResponseTest, ParsesAllItems)
{
    ASSERT_THAT(medias, SizeIs(2));
}

TEST_F(ParsingFeedResponseTest, ParsesLink)
{
    ASSERT_THAT(medias[0].mLink, StrEq("http://instagr.am/p/BXsFz/"));
}

TEST_F(ParsingFeedResponseTest, ParsesCaption)
{
    ASSERT_THAT(medias[0].mCaption, StrEq("escalera"));
}

TEST_F(ParsingFeedResponseTest, ReturnsEmptyCaptionIfNotReturned)
{
    ASSERT_THAT(medias[1].mCaption, StrEq(""));
}

TEST_F(ParsingFeedResponseTest, ParsesCreatedTime)
{
    ASSERT_THAT(medias[0].mCreatedTime, StrEq("1296748524"));
}

// TODO type, filter, tags, id, images/video, location, user