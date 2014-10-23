#include "ApiUrls.h"

#include <boost/format.hpp>
#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class NonAuthenticatedApiUrlsTest : public Test
{
protected:
    std::string clientId{ "clientid" };
    ApiUrlsPtr apiUrls{ CreateNonauthenticatedApiUrls(clientId) };
};

TEST_F(NonAuthenticatedApiUrlsTest, ConstructsUserByIdUrl)
{
    const std::string userId = "123";
    ASSERT_THAT(apiUrls->getUserById(userId), StrEq("https://api.instagram.com/v1/users/" + userId + "?client_id="+clientId));
}

TEST_F(NonAuthenticatedApiUrlsTest, ConstructsPopularMediasUrl)
{
    const std::string userId = "123";
    ASSERT_THAT(apiUrls->getPopularMedias(), StrEq("https://api.instagram.com/v1/media/popular?client_id=" + clientId));
}

class AuthenticatedApiUrlsTest : public Test
{
protected:
    std::string token{ "token" };
    ApiUrlsPtr apiUrls{ CreateAuthenticatedApiUrls(token) };
};

TEST_F(AuthenticatedApiUrlsTest, ConstructsUserByIdUrl)
{
    const std::string userId = "123";
    ASSERT_THAT(apiUrls->getUserById(userId), StrEq("https://api.instagram.com/v1/users/" + userId + "?access_token=" + token));
}

TEST_F(AuthenticatedApiUrlsTest, ConstructsUserFeedUrl)
{
    const int count = 10;
    const std::string minId = "20";
    const std::string maxId = "30";

    const std::string getFeedUrl = boost::str(boost::format("https://api.instagram.com/v1/users/self/feed?access_token=%1%&count=%2%&min_id=%3%&max_id=%4%") 
        % token % count % minId % maxId);
    ASSERT_THAT(apiUrls->getFeed(count, minId, maxId), StrEq(getFeedUrl));
}

TEST_F(AuthenticatedApiUrlsTest, ConstructsUserFeedWithoutCount)
{
    const std::string minId = "20";
    const std::string maxId = "30";

    const std::string getFeedUrl = boost::str(boost::format("https://api.instagram.com/v1/users/self/feed?access_token=%1%&min_id=%2%&max_id=%3%")
        % token % minId % maxId);
    ASSERT_THAT(apiUrls->getFeed(0, minId, maxId), StrEq(getFeedUrl));
}

TEST_F(AuthenticatedApiUrlsTest, ConstructsUserFeedWithoutCountAndMinId)
{
    const std::string maxId = "30";

    const std::string getFeedUrl = boost::str(boost::format("https://api.instagram.com/v1/users/self/feed?access_token=%1%&max_id=%2%")
        % token % maxId);
    ASSERT_THAT(apiUrls->getFeed(0, std::string(), maxId), StrEq(getFeedUrl));
}

TEST_F(AuthenticatedApiUrlsTest, ConstructsUserFeedWithoutParams)
{
    const std::string getFeedUrl = boost::str(boost::format("https://api.instagram.com/v1/users/self/feed?access_token=%1%") % token);
    ASSERT_THAT(apiUrls->getFeed(0, std::string(), std::string()), StrEq(getFeedUrl));
}
