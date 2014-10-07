#include "ClientImpl.h"
#include "CurlApiImpl.h"
#include "CurlImpl.h"
#include "ExceptionHelpers.h"
#include "ServerResponse.h"
#include "UserImpl.h"

using namespace Instagram;


ClientImpl::ClientImpl(CurlPtr curl, ApiUrlsPtr apiUrls) :
    mCurl(curl),
    mApiUrls(apiUrls)
{
}

UserPtr ClientImpl::findUserById(const std::string& id) const
{
    const std::string responseString = mCurl->get(mApiUrls->getUserById(id));
    ServerResponse response(responseString);
    return UserPtr(new UserImpl(response.parseUser()));
}

ClientPtr Instagram::CreateClient(const std::string& clientId)
{
    CurlApiPtr curlApi(new CurlApiImpl);
    CurlPtr curl(new CurlImpl(curlApi));
    return ClientPtr(new ClientImpl(curl, CreateNonauthenticatedApiUrls(clientId)));
}

