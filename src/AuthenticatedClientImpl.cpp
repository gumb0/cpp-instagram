#include "AuthenticatedClientImpl.h"
#include "CurlApiImpl.h"
#include "CurlImpl.h"
#include "ServerResponse.h"

#include <boost/format.hpp>

using namespace Instagram;

namespace
{
    const std::string GET_FEED_TEMPLATE = "https://api.instagram.com/v1/users/self/feed?count=%1%&min_id=%2%&max_id=%3%&access_token=%4%";
}

AuthenticatedClientImpl::AuthenticatedClientImpl(CurlPtr curl, const std::string& accessToken) :
    mCurl(curl),
    mAccessToken(accessToken)
{
}

UserPtr AuthenticatedClientImpl::findUserById(const std::string& id) const
{
    return UserPtr();
}

Feed AuthenticatedClientImpl::getFeed(int count, int minId, int maxId) const
{
    // TODO DRY
    const std::string responseString = mCurl->get(constructGetFeedRequestUrl(count, minId, maxId));
    ServerResponse response(responseString);
    return response.parseFeed();
}

std::string AuthenticatedClientImpl::constructGetFeedRequestUrl(int count, int minId, int maxId) const
{
    return boost::str(boost::format(GET_FEED_TEMPLATE) % count % minId % maxId % mAccessToken);
}

AuthenticatedClientPtr Instagram::CreateAuthenticatedClient(const std::string& accessToken)
{
    CurlApiPtr curlApi(new CurlApiImpl);
    CurlPtr curl(new CurlImpl(curlApi));
    return AuthenticatedClientPtr(new AuthenticatedClientImpl(curl, accessToken));
}

