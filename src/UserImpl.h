#ifndef CPP_INSTAGRAM_IMPL_USER_IMPL_H
#define CPP_INSTAGRAM_IMPL_USER_IMPL_H

#include "User.h"
#include "UserInfo.h"

namespace Instagram
{
    class UserImpl : public User
    {
    public:
        explicit UserImpl(const UserInfo& userInfo);

        virtual std::string getId() const;
        virtual std::string getUsername() const;
        virtual std::string getFullName() const;
        virtual std::string getProfilePicture() const;
        virtual std::string getBio() const;
        virtual std::string getWebsite() const;
        virtual unsigned int getMediaCount() const;
        virtual unsigned int getFollowsCount() const;
        virtual unsigned int getFollowedByCount() const;

    private:
        const UserInfo mUserInfo;
    };
}

#endif
