#include "AuthenticatedClientImpl.h"
#include "MockCurl.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class AuthenticatedClientTest : public Test
{
protected:
    virtual void SetUp()
    {
        curl.reset(new MockCurl);

        client.reset(new AuthenticatedClientImpl(curl, token));
    }

    std::shared_ptr<MockCurl> curl;
    std::unique_ptr<AuthenticatedClient> client;
    const std::string token { "token" };
};

// TODO test findUserById

TEST_F(AuthenticatedClientTest, GetsFeed)
{
    const int count = 10;
    const int minId = 0;
    const int maxId = 10;
    const std::string request = std::string("https://api.instagram.com/v1/users/self/feed?") + 
        "count=" + std::to_string(count) + "&min_id=" + std::to_string(minId) + "&max_id=" + std::to_string(maxId) +
        "&access_token=" + token;

    const std::string response = R"({ "meta":{"code": 200}, "data":[{ "location": { "id": "833", "latitude" : 37.77956816727314, "longitude" : -122.41387367248539,
        "name" : "Civic Center BART" }, "comments": { "count": 0, "data" : [] }, "caption" : null, "link" : "http://instagr.am/p/BXsFz/",
            "likes" : { "count": 0, "data" : [] }, "created_time": "1296748524", "images" : { "low_resolution": 
            { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_6.jpg", "width" : 306, "height" : 306 },
            "thumbnail" : { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_5.jpg", "width" : 150, "height" : 150 },
            "standard_resolution" : { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_7.jpg", "width" : 612, "height" : 612 } },
            "type": "image", "users_in_photo" : [], "filter" : "Earlybird", "tags" : [], "id" : "22987123", "user" : { "username": "kevin",
            "full_name" : "Kevin S", "profile_picture" : "http://distillery.s3.amazonaws.com/profiles/profile_3_75sq_1295574122.jpg",
            "id" : "3" } } ] })";

    EXPECT_CALL(*curl, get(StrEq(request))).WillOnce(Return(response));

    Feed feed = client->getFeed(count, minId, maxId);
    ASSERT_THAT(feed, Not(IsEmpty()));
}
