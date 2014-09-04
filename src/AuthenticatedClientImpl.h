#ifndef CPP_INSTAGRAM_IMPL_AUTHENTICATED_CLIENT_IMPL_H
#define CPP_INSTAGRAM_IMPL_AUTHENTICATED_CLIENT_IMPL_H

#include "AuthenticatedClient.h"
#include "Curl.h"

namespace Instagram
{
    class AuthenticatedClientImpl : public AuthenticatedClient
    {
    public:
        AuthenticatedClientImpl(CurlPtr curl, const std::string& accessToken);

        virtual UserPtr findUserById(const std::string& id) const;
        virtual Feed getFeed(int count, int minId, int maxId) const;

    private:
        std::string constructGetFeedRequestUrl(int count, int minId, int maxId) const;

    private:
        CurlPtr mCurl;
        const std::string mAccessToken;
    };
}

#endif
