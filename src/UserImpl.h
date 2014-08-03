#ifndef CPP_INSTAGRAM_IMPL_USER_IMPL_H
#define CPP_INSTAGRAM_IMPL_USER_IMPL_H

#include "User.h"

namespace Instagram
{
    class UserImpl : public User
    {
    public:
        UserImpl(const std::string& jsonData);

        std::string getId() const;

    private:
        std::string mId;
    };
}

#endif
