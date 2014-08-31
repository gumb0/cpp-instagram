#ifndef CPP_INSTAGRAM_USER_H
#define CPP_INSTAGRAM_USER_H

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{
    class User : NonCopyable
    {
    public:
        virtual std::string getId() const = 0;
        virtual std::string getUsername() const = 0;
        virtual std::string getFullName() const = 0;
        virtual std::string getProfilePicture() const = 0;
        virtual std::string getBio() const = 0;
        virtual std::string getWebsite() const = 0;
        virtual int getMediaCount() const = 0;
        virtual int getFollowsCount() const = 0;
        virtual int getFollowedByCount() const = 0;
    };

    typedef std::shared_ptr<User> UserPtr;
}

#endif