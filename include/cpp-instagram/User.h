#ifndef CPP_INSTAGRAM_USER_H
#define CPP_INSTAGRAM_USER_H

#include <memory>
#include <string>

namespace Instagram
{
    struct UserCounts
    {
        unsigned int media;
        unsigned int follows;
        unsigned int followedBy;
    };

    class User
    {
    public:
        virtual ~User() {}

        virtual std::string getId() const = 0;
        virtual std::string getUsername() const = 0;
        virtual std::string getFullName() const = 0;
        virtual std::string getProfilePicture() const = 0;
    };

    typedef std::shared_ptr<User> UserPtr;
}

#endif