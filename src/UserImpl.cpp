#include "UserImpl.h"
#include "ExceptionHelpers.h"

#include <json/json.h>

using namespace Instagram;

namespace
{
    const char* JSON_KEY_META = "meta";
    const char* JSON_KEY_CODE = "code";
    const char* JSON_KEY_DATA = "data";
    const char* JSON_KEY_ID = "id";
    const char* JSON_KEY_USERNAME = "username";

    const Json::Int RESPONSE_CODE_OK = 200;
}

UserImpl::UserImpl(const UserInfo& userInfo) : mUserInfo(userInfo)
{
}

std::string UserImpl::getId() const
{
    return mUserInfo.mId;
}

std::string UserImpl::getUsername() const
{
    return mUserInfo.mUsername;
}
