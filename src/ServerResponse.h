#ifndef CPP_INSTAGRAM_IMPL_SERVER_RESPONSE_H
#define CPP_INSTAGRAM_IMPL_SERVER_RESPONSE_H

#include "UserInfo.h"

#include <json/json.h>

namespace Instagram
{
    class ServerResponse
    {
    public:
        explicit ServerResponse(const std::string& response);

        UserInfo parseUser() const;

    private:
        std::string getStringValue(const char* key) const;

    private:
        const Json::Value mData;
    };
}

#endif
