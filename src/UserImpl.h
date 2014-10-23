#ifndef CPP_INSTAGRAM_IMPL_USER_IMPL_H
#define CPP_INSTAGRAM_IMPL_USER_IMPL_H

#include "Curl.h"
#include "User.h"
#include "UserInfo.h"

namespace Instagram
{
    class UserImpl : public User
    {
    public:
        UserImpl(CurlPtr curl, const UserInfo& userInfo);

        virtual std::string getId() const;

        virtual std::string getUsername() const;

        virtual std::string getFullName() const;

        virtual std::string getProfilePictureUrl() const;

        virtual void downloadProfilePicture(const std::string& localPath) const;

        virtual std::string getBio() const;

        virtual std::string getWebsite() const;

        virtual int getMediaCount() const;

        virtual int getFollowsCount() const;

        virtual int getFollowedByCount() const;

    private:
        CurlPtr mCurl;
        const UserInfo mUserInfo;
    };

    UserPtr CreateUserImpl(CurlPtr curl, const UserInfo& userInfo);
}

#endif
