#include "ClientImpl.h"
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
    const std::string responseString = mCurl->get(constuctGetUserRequestUrl(id));
    ServerResponse response(responseString);
    return UserPtr(new UserImpl(response.parseUser()));
}

std::string ClientImpl::constuctGetUserRequestUrl(const std::string& id) const
{
    return boost::str(boost::format(GET_USER_INFO_TEMPLATE) % id % mClientId);
}
