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
        // TODO somehow make params optional
        virtual Feed getFeed(int count, int minId, int maxId) const = 0;
    };

    typedef std::shared_ptr<AuthenticatedClient> AuthenticatedClientPtr;

    AuthenticatedClientPtr CreateAuthenticatedClient(const std::string& accessToken);
}

#endif