#ifndef CPP_INSTAGRAM_IMPL_USER_IMPL_H
#define CPP_INSTAGRAM_IMPL_USER_IMPL_H

#include "User.h"

namespace Instagram
{
    class UserImpl : public User
    {
    public:
        explicit UserImpl(const std::string& jsonData);

        virtual std::string getId() const;
        virtual std::string getUsername() const;

    private:
        std::string mId;
        std::string mUsername;
    };
}

#endif
