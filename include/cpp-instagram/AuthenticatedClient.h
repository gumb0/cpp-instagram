#ifndef CPP_INSTAGRAM_AUTHENTICATED_CLIENT_H
#define CPP_INSTAGRAM_AUTHENTICATED_CLIENT_H

#include "Client.h"
#include "Media.h"

#include <memory>
#include <string>

namespace Instagram
{
    class AuthenticatedClient : public Client
    {
    public:
        // 0 passed to any argument will make it ignored
        virtual Feed getFeed(int count = 0, int minId = 0, int maxId = 0) const = 0;
    };

    typedef std::shared_ptr<AuthenticatedClient> AuthenticatedClientPtr;

    AuthenticatedClientPtr CreateAuthenticatedClient(const std::string& accessToken);
}

#endif