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
                "tags" : ["duxton","vsco","tree","singapore"], 
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
                    "low_bandwidth": {
                        "url": "http://distilleryvesper9-13.ak.instagram.com/090d06dad9cd11e2aa0912313817975d_103.mp4",
                        "width": 480,
                        "height": 480
                    },
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
            },
            { 
                "tags":[],
                "type":"image",
                "location": {"latitude": 51.919455, "longitude": 4.481111667 },
                "comments": { "count": 0, "data" : [] }, 
                "filter":"Normal",
                "created_time":"1413402734",
                "link":"http:\/\/instagram.com\/p\/uL4AtZokHI\/",
                "likes" : { "count": 0, "data" : [] }, 
                "images": { 
                        "low_resolution":{"url":"http:\/\/scontent-a.cdninstagram.com\/hphotos-xfa1\/t51.2885-15\/10724027_310739932447060_230232520_a.jpg","width":306,"height":306},
                        "thumbnail":{"url":"http:\/\/scontent-a.cdninstagram.com\/hphotos-xfa1\/t51.2885-15\/10724027_310739932447060_230232520_s.jpg","width":150,"height":150},
                        "standard_resolution":{"url":"http:\/\/scontent-a.cdninstagram.com\/hphotos-xfa1\/t51.2885-15\/10724027_310739932447060_230232520_n.jpg","width":640,"height":640}},
                "users_in_photo" : [], 
                "caption": null,
                "user_has_liked":false,
                "id":"832004895533056456_219872191",
                "user":{"username":"love_aesthetics","website":"","profile_picture":"http:\/\/images.ak.instagram.com\/profiles\/profile_219872191_75sq_1389476691.jpg","full_name":"Ivania Carpio","bio":"","id":"219872191"}
           } ] })";

        ServerResponse response(json);

        medias = response.parseFeed();
    }

protected:
    std::vector<MediaInfo> medias;
};

TEST_F(ParsingFeedResponseTest, ParsesAllItems)
{
    ASSERT_THAT(medias, SizeIs(3));
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

TEST_F(ParsingFeedResponseTest, ParsesImageType)
{
    ASSERT_THAT(medias[0].mType, Eq(MediaType::Image));
}

TEST_F(ParsingFeedResponseTest, ParsesVideoType)
{
    ASSERT_THAT(medias[1].mType, Eq(MediaType::Video));
}

TEST_F(ParsingFeedResponseTest, ParsesFilter)
{
    ASSERT_THAT(medias[0].mFilter, StrEq("Earlybird"));
}

TEST_F(ParsingFeedResponseTest, ParsesId)
{
    ASSERT_THAT(medias[0].mId, StrEq("22987123"));
}

TEST_F(ParsingFeedResponseTest, ParsesTags)
{
    ASSERT_THAT(medias[0].mTags, ElementsAre(StrEq("duxton"), StrEq("vsco"), StrEq("tree"), StrEq("singapore")));
}

TEST_F(ParsingFeedResponseTest, ParsesImages)
{
    ASSERT_THAT(medias[0].mImageInfo, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesLowResolutionImage)
{
    ASSERT_THAT(medias[0].mImageInfo->mLowResolution, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesLowResolutionImageWidth)
{
    ASSERT_THAT(medias[0].mImageInfo->mLowResolution->mWidth, Eq(306));
}

TEST_F(ParsingFeedResponseTest, ParsesLowResolutionImageHeight)
{
    ASSERT_THAT(medias[0].mImageInfo->mLowResolution->mHeight, Eq(306));
}

TEST_F(ParsingFeedResponseTest, ParsesLowResolutionImageUrl)
{
    ASSERT_THAT(medias[0].mImageInfo->mLowResolution->mUrl, StrEq("http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_6.jpg"));
}

TEST_F(ParsingFeedResponseTest, ParsesStandardResolutionImage)
{
    ASSERT_THAT(medias[0].mImageInfo->mStandardResolution, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesThumbnail)
{
    ASSERT_THAT(medias[0].mImageInfo->mThumbnail, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesVideos)
{
    ASSERT_THAT(medias[1].mVideoInfo, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesLowBandwidthVideo)
{
    ASSERT_THAT(medias[1].mVideoInfo->mLowBandwidth, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesLowResolutionVideo)
{
    ASSERT_THAT(medias[1].mVideoInfo->mLowResolution, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesStandardResolutionVideo)
{
    ASSERT_THAT(medias[1].mVideoInfo->mStandardResolution, NotNull());
}

TEST_F(ParsingFeedResponseTest, ParsesLocation)
{
    ASSERT_THAT(medias[0].mLocationInfo, NotNull());
}

TEST_F(ParsingFeedResponseTest, ReturnsNullIfNoLocation)
{
    ASSERT_THAT(medias[1].mLocationInfo, IsNull());
}

TEST_F(ParsingFeedResponseTest, ReturnsLocationId)
{
    ASSERT_THAT(medias[0].mLocationInfo->mId, StrEq("833"));
}

TEST_F(ParsingFeedResponseTest, ReturnsEmptyLocationIdIfNotReturned)
{
    ASSERT_THAT(medias[2].mLocationInfo->mId, StrEq(""));
}

TEST_F(ParsingFeedResponseTest, ReturnsLocationLat)
{
    ASSERT_THAT(medias[0].mLocationInfo->mLatitude, DoubleEq(37.77956816727314));
}

TEST_F(ParsingFeedResponseTest, ReturnsLocationLon)
{
    ASSERT_THAT(medias[0].mLocationInfo->mLongitude, DoubleEq(-122.41387367248539));
}

TEST_F(ParsingFeedResponseTest, ReturnsLocationName)
{
    ASSERT_THAT(medias[0].mLocationInfo->mName, StrEq("Civic Center BART"));
}

TEST_F(ParsingFeedResponseTest, ReturnsEmptyNameIfNotReturned)
{
    ASSERT_THAT(medias[2].mLocationInfo->mName, StrEq(""));
}

// TODO user

TEST(ParsingIncorrectFeedResponseTest, ThrowsIfJsonHasNoId)
{
    ServerResponse response(R"({ "meta":{"code": 200 }, 
            "data":[
            { 
                "link" : "http://instagr.am/p/BXsFz/",
                "likes" : { "count": 0, "data" : [] }, 
                "created_time": "1296748524", 
                "type": "unknown", 
                "id" : "22987123", 
                "user" : { 
                    "username": "kevin",
                    "full_name" : "Kevin S", 
                    "profile_picture" : "http://distillery.s3.amazonaws.com/profiles/profile_3_75sq_1295574122.jpg",
                    "id" : "3"
                 } 
            }]})");

    ASSERT_THROW(response.parseFeed(), Instagram::Exception);
}
