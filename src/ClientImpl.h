#ifndef CPP_INSTAGRAM_IMPL_CLIENT_IMPL_H
#define CPP_INSTAGRAM_IMPL_CLIENT_IMPL_H

#include "ApiUrls.h"
#include "Client.h"
#include "Curl.h"

namespace Instagram
{
    class ClientImpl : public Client
    {
    public:
        ClientImpl(CurlPtr curl, ApiUrlsPtr apiUrls);

        virtual UserPtr findUserById(const std::string& id) const;

    private:
        std::string constructGetUserRequestUrl(const std::string& id) const;

    private:
        CurlPtr mCurl;
        const ApiUrlsPtr mApiUrls;
    };
}

#endif
