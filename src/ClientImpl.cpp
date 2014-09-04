#include "ClientImpl.h"
#include "CurlApiImpl.h"
#include "CurlImpl.h"
#include "ExceptionHelpers.h"
#include "ServerResponse.h"
#include "UserImpl.h"

#include <boost/format.hpp>

using namespace Instagram;

namespace
{
    const std::string GET_USER_INFO_TEMPLATE = "https://api.instagram.com/v1/users/%1%?client_id=%2%";
}

ClientImpl::ClientImpl(CurlPtr curl, const std::string& clientId) :
    mCurl(curl),
    mClientId(clientId)
{
}

UserPtr ClientImpl::findUserById(const std::string& id) const
{
    const std::string responseString = mCurl->get(constructGetUserRequestUrl(id));
    ServerResponse response(responseString);
    return UserPtr(new UserImpl(response.parseUser()));
}

std::string ClientImpl::constructGetUserRequestUrl(const std::string& id) const
{
    return boost::str(boost::format(GET_USER_INFO_TEMPLATE) % id % mClientId);
}

ClientPtr Instagram::CreateClient(const std::string& clientId)
{
    CurlApiPtr curlApi(new CurlApiImpl);
    CurlPtr curl(new CurlImpl(curlApi));
    return ClientPtr(new ClientImpl(curl, clientId));
}

