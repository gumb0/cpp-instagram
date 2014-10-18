#include "ClientImpl.h"
#include "CurlApiImpl.h"
#include "CurlImpl.h"
#include "ExceptionHelpers.h"
#include "MediaImpl.h"
#include "ServerResponse.h"
#include "StdioApiImpl.h"
#include "UserImpl.h"

#include <algorithm>
#include <functional>

using namespace Instagram;

namespace
{
    CurlPtr CreateCurl()
    {
        CurlApiPtr curlApi(new CurlApiImpl);
        StdioApiPtr stdio(new StdioApiImpl);
        return CurlPtr(new CurlImpl(curlApi, stdio));
    }
}

ClientImpl::ClientImpl(CurlPtr curl, ApiUrlsPtr apiUrls) :
    mCurl(curl),
    mApiUrls(apiUrls)
{
}

UserPtr ClientImpl::findUserById(const std::string& id) const
{
    ServerResponse response(getFromUrl(mApiUrls->getUserById(id)));
    return UserPtr(new UserImpl(response.parseUser()));
}

ServerResponse ClientImpl::getFromUrl(const std::string& url) const
{
    return ServerResponse(mCurl->get(url));
}

Feed ClientImpl::getFeed(int count /* = 0 */, const std::string& minId /* = std::string() */, const std::string& maxId /* = std::string() */) const
{
    ServerResponse response(getFromUrl(mApiUrls->getFeed(count, minId, maxId)));
    std::vector<MediaInfo> medias = response.parseFeed();

    Feed feed;
    std::transform(medias.begin(), medias.end(), std::back_inserter(feed), 
        std::bind(CreateMediaImpl, mCurl, std::placeholders::_1));

    return feed;
}

ClientPtr Instagram::CreateClient(const std::string& clientId)
{
    return ClientPtr(new ClientImpl(CreateCurl(), CreateNonauthenticatedApiUrls(clientId)));
}

AuthenticatedClientPtr Instagram::CreateAuthenticatedClient(const std::string& accessToken)
{
    return AuthenticatedClientPtr(new ClientImpl(CreateCurl(), CreateAuthenticatedApiUrls(accessToken)));
}

