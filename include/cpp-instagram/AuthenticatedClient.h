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
        // 0 passed to cout will make it ignored
        // empty string passed to minId/maxId makes them ignored
        virtual Feed getFeed(int count = 0, const std::string& minId = std::string(), const std::string& maxId = std::string()) const = 0;
    };

    typedef std::shared_ptr<AuthenticatedClient> AuthenticatedClientPtr;

    AuthenticatedClientPtr CreateAuthenticatedClient(const std::string& accessToken);
}

#endif