#include "UserImpl.h"
#include "ExceptionHelpers.h"

#include <json/json.h>

using namespace Instagram;

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

std::string UserImpl::getFullName() const
{
    return mUserInfo.mFullName;
}

std::string UserImpl::getProfilePicture() const
{
    return mUserInfo.mProfilePicture;
}
