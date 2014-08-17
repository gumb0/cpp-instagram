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

std::string UserImpl::getBio() const
{
    return mUserInfo.mBio;
}

std::string UserImpl::getWebsite() const
{
    return mUserInfo.mWebsite;
}

unsigned int UserImpl::getMediaCount() const
{
    return mUserInfo.mCounts.media;
}

unsigned int UserImpl::getFollowsCount() const
{
    return mUserInfo.mCounts.follows;
}

unsigned int UserImpl::getFollowedByCount() const
{
    return mUserInfo.mCounts.followedBy;
}
