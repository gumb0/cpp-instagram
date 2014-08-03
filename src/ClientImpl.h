#ifndef CPP_INSTAGRAM_IMPL_CLIENT_IMPL_H
#define CPP_INSTAGRAM_IMPL_CLIENT_IMPL_H

#include "Client.h"
#include "Curl.h"

namespace Instagram
{
    class ClientImpl : public Client
    {
    public:
        ClientImpl(CurlPtr curl) : mCurl(curl)
        {
        }

        // TODO move to impl
        void init(const std::string& clienId)
        {

        }

        User findUserById(const std::string& id) const
        {
            std::string userJson = mCurl->get(std::string("http://instagram.com/users/") + id);
            return User(userJson);
        }

    private:
        CurlPtr mCurl;
    };
}

#endif
