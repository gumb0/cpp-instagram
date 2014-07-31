#ifndef CPP_INSTAGRAM_CLIENT_H
#define CPP_INSTAGRAM_CLIENT_H

#include "User.h"

#include <string>

namespace Instagram
{
    class Client
    {
    public:
        // TODO move to impl
        void init(const std::string& clienId)
        {

        }

        User findUserById(const std::string& id) const
        {
            return User();
        }
    };
}

#endif