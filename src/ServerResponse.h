#ifndef CPP_INSTAGRAM_IMPL_SERVER_RESPONSE_H
#define CPP_INSTAGRAM_IMPL_SERVER_RESPONSE_H

#include "UserInfo.h"

namespace Instagram
{
    class ServerResponse
    {
    public:
        UserInfo parseUser(const std::string& jsonData);
    };
}

#endif
