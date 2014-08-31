#ifndef CPP_INSTAGRAM_CLIENT_H
#define CPP_INSTAGRAM_CLIENT_H

#include "NonCopyable.h"
#include "User.h"

#include <memory>
#include <string>

namespace Instagram
{
    class Client : NonCopyable
    {
    public:
        virtual UserPtr findUserById(const std::string& id) const = 0;
    };

    typedef std::shared_ptr<Client> ClientPtr;

    ClientPtr CreateClient(const std::string& clientId);
}

#endif