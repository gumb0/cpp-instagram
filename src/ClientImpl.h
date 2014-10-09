#ifndef CPP_INSTAGRAM_IMPL_CLIENT_IMPL_H
#define CPP_INSTAGRAM_IMPL_CLIENT_IMPL_H

#include "ApiUrls.h"
#include "AuthenticatedClient.h"
#include "Curl.h"

namespace Instagram
{
    class ServerResponse;

    // Both Client and AuthenticatedClient interfaces are implemented by ClientImpl, 
    // since the only difference is in using either client_id or access_token in API URLs
    // (this difference is encapsulated in ApiUrls class)
    class ClientImpl : public AuthenticatedClient
    {
    public:
        ClientImpl(CurlPtr curl, ApiUrlsPtr apiUrls);

        // Client methods
        virtual UserPtr findUserById(const std::string& id) const;

        // AuthenticatedClient methods

        // 0 passed to cout will make it ignored
        // empty string passed to minId/maxId makes them ignored
        virtual Feed getFeed(int count = 0, const std::string& minId = std::string(), const std::string& maxId = std::string()) const;

    private:
        ServerResponse getFromUrl(const std::string& url) const;

    private:
        CurlPtr mCurl;
        const ApiUrlsPtr mApiUrls;
    };
}

#endif
