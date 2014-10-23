#include "ClientImpl.h"
#include "MockCurl.h"
#include "User.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

namespace
{
    const std::string MEDIA_LIST_RESPONSE = R"({ "meta":{"code": 200}, "data":[{ "location": { "id": "833", "latitude" : 37.77956816727314, "longitude" : -122.41387367248539,
        "name" : "Civic Center BART" }, "comments": { "count": 0, "data" : [] }, "caption" : null, "link" : "http://instagr.am/p/BXsFz/",
        "likes" : { "count": 0, "data" : [] }, "created_time": "1296748524", "images" : { "low_resolution": 
        { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_6.jpg", "width" : 306, "height" : 306 },
        "thumbnail" : { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_5.jpg", "width" : 150, "height" : 150 },
        "standard_resolution" : { "url": "http://distillery.s3.amazonaws.com/media/2011/02/03/efc502667a554329b52d9a6bab35b24a_7.jpg", "width" : 612, "height" : 612 } },
        "type": "image", "users_in_photo" : [], "filter" : "Earlybird", "tags" : [], "id" : "22987123", "user" : { "username": "kevin",
        "full_name" : "Kevin S", "profile_picture" : "http://distillery.s3.amazonaws.com/profiles/profile_3_75sq_1295574122.jpg",
        "id" : "3" } } ] })";
}

class ClientTest : public Test
{
protected:
    virtual void SetUp()
    {
        curl.reset(new MockCurl);

        client.reset(new ClientImpl(curl, CreateNonauthenticatedApiUrls(clientId)));
    }

    std::shared_ptr<MockCurl> curl;
    std::unique_ptr<Client> client;
    const std::string clientId = "client-id";
};

TEST_F(ClientTest, FindsUserById)
{
    const std::string id = "1574083";

    const std::string request = std::string("https://api.instagram.com/v1/users/") + id + "?client_id=" + clientId;
    std::string response = "{\"meta\":{\"code\":200},\"data\":{\"username\":\"snoopdogg\",\"bio\":\"I smoked out the whitehouse !\",\"website\":\"http://bit.ly/1onGzhG\",\"profile_picture\":\"http://images.ak.instagram.com/profiles/profile_1574083_75sq_1381898834.jpg\", \"full_name\":\"snoopdogg\", \"counts\" : {\"media\":7453, \"followed_by\" : 3370805, \"follows\" : 698}, \"id\" : \"1574083\"}}";
    EXPECT_CALL(*curl, get(StrEq(request))).WillOnce(Return(response));

    UserPtr user = client->findUserById(id);
    ASSERT_THAT(user->getId(), StrEq(id));
}

TEST_F(ClientTest, GetsPopularMedias)
{
    const std::string request = std::string("https://api.instagram.com/v1/media/popular?client_id=" + clientId);
    EXPECT_CALL(*curl, get(StrEq(request))).WillOnce(Return(MEDIA_LIST_RESPONSE));

    Feed medias = client->getPopularMedias();
    ASSERT_THAT(medias, SizeIs(1));
}

class AuthenticatedClientTest : public Test
{
protected:
    virtual void SetUp()
    {
        curl.reset(new MockCurl);

        client.reset(new ClientImpl(curl, CreateAuthenticatedApiUrls(token)));
    }

    std::shared_ptr<MockCurl> curl;
    std::unique_ptr<AuthenticatedClient> client;
    const std::string token = "token";
};

TEST_F(AuthenticatedClientTest, GetsFeed)
{
    const int count = 10;
    const std::string minId = "1";
    const std::string maxId = "10";
    const std::string request = std::string("https://api.instagram.com/v1/users/self/feed?") +
        "access_token=" + token +
        "&count=" + std::to_string(count) + "&min_id=" + minId + "&max_id=" + maxId;

    EXPECT_CALL(*curl, get(StrEq(request))).WillOnce(Return(MEDIA_LIST_RESPONSE));

    Feed feed = client->getFeed(count, minId, maxId);
    ASSERT_THAT(feed, SizeIs(1));
}
