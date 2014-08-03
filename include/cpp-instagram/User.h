#ifndef CPP_INSTAGRAM_USER_H
#define CPP_INSTAGRAM_USER_H

#include <memory>
#include <string>

namespace Instagram
{
    class User
    {
    public:
        virtual ~User() {}

        virtual std::string getId() const = 0;
    };

    typedef std::shared_ptr<User> UserPtr;
}

#endif