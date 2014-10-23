#include "UserImpl.h"
#include "ExceptionHelpers.h"

using namespace Instagram;

UserImpl::UserImpl(CurlPtr curl, const UserInfo& userInfo) : 
    mCurl(curl),
    mUserInfo(userInfo)
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

std::string UserImpl::getProfilePictureUrl() const
{
    return mUserInfo.mProfilePicture;
}

void UserImpl::downloadProfilePicture(const std::string& localPath) const
{
    mCurl->download(mUserInfo.mProfilePicture, localPath);
}

std::string UserImpl::getBio() const
{
    return mUserInfo.mBio;
}

std::string UserImpl::getWebsite() const
{
    return mUserInfo.mWebsite;
}

int UserImpl::getMediaCount() const
{
    return mUserInfo.mCounts.mMedia;
}

int UserImpl::getFollowsCount() const
{
    return mUserInfo.mCounts.mFollows;
}

int UserImpl::getFollowedByCount() const
{
    return mUserInfo.mCounts.mFollowedBy;
}


UserPtr Instagram::CreateUserImpl(CurlPtr curl, const UserInfo& userInfo)
{
    return UserPtr(new UserImpl(curl, userInfo));
}
