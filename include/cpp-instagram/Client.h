#ifndef CPP_INSTAGRAM_CLIENT_H
#define CPP_INSTAGRAM_CLIENT_H

#include "Media.h"
#include "NonCopyable.h"
#include "User.h"
#include "Tag.h"

#include <memory>
#include <string>

namespace Instagram
{
    class Client : NonCopyable
    {
    public:
        virtual UserPtr findUserById(const std::string& id) const = 0;
        virtual MediaList getPopularMedias() const = 0;
        virtual MediaList getRecentMediasByTag(const std::string& tag, int count = 0) const = 0; // TODO: add more API parameters via options object
    };

    typedef std::shared_ptr<Client> ClientPtr;

    ClientPtr CreateClient(const std::string& clientId);
}

#endif
