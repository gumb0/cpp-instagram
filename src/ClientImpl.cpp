#include "ClientImpl.h"
#include "CurlApiImpl.h"
#include "CurlImpl.h"
#include "ExceptionHelpers.h"
#include "ServerResponse.h"
#include "UserImpl.h"

using namespace Instagram;

namespace
{
    CurlPtr CreateCurl()
    {
        CurlApiPtr curlApi(new CurlApiImpl);
        return CurlPtr(new CurlImpl(curlApi));
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

Feed ClientImpl::getFeed(int count /* = 0 */, int minId /* = 0 */, int maxId /* = 0 */) const
{
    ServerResponse response(getFromUrl(mApiUrls->getFeed(count, minId, maxId)));
    return response.parseFeed();
}

ClientPtr Instagram::CreateClient(const std::string& clientId)
{
    return ClientPtr(new ClientImpl(CreateCurl(), CreateNonauthenticatedApiUrls(clientId)));
}

AuthenticatedClientPtr Instagram::CreateAuthenticatedClient(const std::string& accessToken)
{
    return AuthenticatedClientPtr(new ClientImpl(CreateCurl(), CreateAuthenticatedApiUrls(accessToken)));
}

